#include "game.h"
#include "log.h"

#define FRAMERATE_LIMIT 60

Game::Game() {
  window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Sprite test");
  ticker = new Ticker(FRAMERATE_LIMIT);
  view = window->GetDefaultView();
  center = view.GetCenter();
  window->SetView(view);
  scroll = Move::NONE;

  imageMgr = new ImageManager();
  cursor = new Cursor(window, imageMgr);
  set = new TileSet(imageMgr, 40, 40);
  cannon = new Cannon(imageMgr, set);
}

Game::~Game() {
  delete cannon;
  delete set;
  delete cursor;
  delete imageMgr;
  delete ticker;
  delete window;
}

void Game::run() {
  running = true;
  while (running) {
    sf::Event evt;
    while (window->GetEvent(evt)) {
      switch (evt.Type) {
        case sf::Event::Closed:
          exit();
          break;
        case sf::Event::Resized:
          onResized(evt);
          break;
        case sf::Event::MouseButtonPressed:
          onMouseButtonPressed(evt);
          break;
        case sf::Event::MouseButtonReleased:
          onMouseButtonReleased(evt);
          break;
        case sf::Event::MouseMoved:
          onMouseMoved(evt);
          break;
        case sf::Event::KeyPressed:
          onKeyPressed(evt);
          break;
        case sf::Event::KeyReleased:
          onKeyReleased(evt);
          break;
        default:
          break;
      }
    }

    if (!running)
      break;

    float delta = ticker->tick();
    if (delta < 0)
      continue;

    update(delta);
    paint();
    window->Display();
  }
}

void Game::exit() {
  running = false;
  window->Close();
}

void Game::scrollTo(const sf::Vector2f &c) {
  center = c;
  view.SetCenter(center);
}

void Game::scrollView(float delta) {
  static const float SCROLL_SPEED = 20;
  float dist = delta * SCROLL_SPEED;
  if (scroll & Move::LEFT)
    center.x -= dist;
  if (scroll & Move::RIGHT)
    center.x += dist;
  if (scroll & Move::UP)
    center.y -= dist;
  if (scroll & Move::DOWN)
    center.y += dist;

  scrollTo(center);
}

void Game::update(float delta) {
  scrollView(delta);
  cannon->update(delta);
}

void Game::paintDebug() {
  static sf::Font font;
  static sf::String out;
  static bool loaded = false;
  if (!loaded) {
    if (!font.LoadFromFile("arial.ttf")) {
      log("Font could not be loaded");
      exit();
      return;
    }

    out.SetFont(font);
    out.SetSize(12);
    out.SetColor(sf::Color::White);
    loaded = true;
  }

  std::ostringstream s;
  s << "FPS: " << ticker->getFramerate();
  out.SetText(s.str());

  out.SetPosition(window->ConvertCoords(0, 0));
  window->Draw(out);
}

void Game::paint() {
  window->Clear(sf::Color::Black);
  set->paint(window);
  cannon->paint(window);
  paintDebug();
  cursor->paint();
}

void Game::onResized(sf::Event evt) {
  view.SetHalfSize(sf::Vector2f(evt.Size.Width / 2.0, evt.Size.Height / 2.0));
}

#define SCROLL_ZONE 20

void Game::onMouseMoved(sf::Event evt) {
  cursor->onMoved(evt.MouseMove);

  scroll = Move::NONE;
  sf::Rect<float> rect = view.GetRect();
  sf::Vector2f cur = cursor->getViewPosition();
  if (cur.x < rect.Left + SCROLL_ZONE)
    scroll = (Move::Type)(scroll | Move::LEFT);
  if (cur.x > rect.Right - SCROLL_ZONE)
    scroll = (Move::Type)(scroll | Move::RIGHT);
  if (cur.y < rect.Top + SCROLL_ZONE)
    scroll = (Move::Type)(scroll | Move::UP);
  if (cur.y > rect.Bottom - SCROLL_ZONE)
    scroll = (Move::Type)(scroll | Move::DOWN);
}

void Game::onMouseButtonPressed(sf::Event evt) {
  switch (evt.MouseButton.Button) {
    case sf::Mouse::Left:
      break;
    default:
      break;
  }
}

void Game::onMouseButtonReleased(sf::Event evt) {
  switch (evt.MouseButton.Button) {
    case sf::Mouse::Left:
      scrollTo(cursor->getViewPosition());
      break;
    default:
      break;
  }
}

void Game::onKeyPressed(sf::Event evt) {
  Move::Type base = cannon->getMove();
  switch (evt.Key.Code) {
    case sf::Key::Right:
      cannon->setMove((Move::Type)(base | Move::FORWARD));
      break;
    case sf::Key::Left:
      cannon->setMove((Move::Type)(base | Move::BACKWARD));
      break;
    case sf::Key::Up:
      cannon->setMove((Move::Type)(base | Move::TURN_CCW));
      break;
    case sf::Key::Down:
      cannon->setMove((Move::Type)(base | Move::TURN_CW));
      break;
    default:
      break;
  }
}

void Game::onKeyReleased(sf::Event evt) {
  Move::Type base = cannon->getMove();
  switch (evt.Key.Code) {
    case sf::Key::Escape:
    case sf::Key::Q:
      exit();
      break;
    case sf::Key::P:
      ticker->togglePause();
      break;
    case sf::Key::Right:
      cannon->setMove((Move::Type)(base & ~Move::FORWARD));
      break;
    case sf::Key::Left:
      cannon->setMove((Move::Type)(base & ~Move::BACKWARD));
      break;
    case sf::Key::Up:
      cannon->setMove((Move::Type)(base & ~Move::TURN_CCW));
      break;
    case sf::Key::Down:
      cannon->setMove((Move::Type)(base & ~Move::TURN_CW));
      break;
    default:
      break;
  }
}
