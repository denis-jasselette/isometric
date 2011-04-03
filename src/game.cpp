#include "game.h"
#include "log.h"

Game::Game() {
  window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Sprite test");
  view = window->GetDefaultView();
  center = view.GetCenter();
  window->SetView(view);
  scroll = Move::NONE;

  imageMgr = new ImageManager();
  cursor = new Cursor(window, imageMgr);
  cannon = new Cannon(imageMgr);
  set = new TileSet(imageMgr, 20, 20);
}

Game::~Game() {
  delete set;
  delete cannon;
  delete cursor;
  delete imageMgr;
  delete window;
}

void Game::run() {
  window->SetFramerateLimit(60);
  bool running = true;
  while (running) {
    sf::Event evt;
    while (window->GetEvent(evt)) {
      switch (evt.Type) {
        case sf::Event::Closed:
          running = false;
          break;
        case sf::Event::Resized:
          onResized(evt);
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

    update();
    paint();
    window->Display();

    /*if (running)
      sleep(1);*/
  }
}

void Game::scrollView() {
  if (scroll & Move::LEFT)
    center.x -= 1;
  if (scroll & Move::RIGHT)
    center.x += 1;
  if (scroll & Move::UP)
    center.y -= 1;
  if (scroll & Move::DOWN)
    center.y += 1;

  view.SetCenter(center);
}

void Game::update() {
  scrollView();
  cannon->update();
}

void Game::paint() {
  window->Clear(sf::Color::Black);
  set->paint(window);
  cannon->paint(window);
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
