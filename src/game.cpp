#include "game.h"
#include "log.h"

Game::Game() {
  window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Sprite test");
  view = window->GetDefaultView();
  center = view.GetCenter();

  imageMgr = new ImageManager();
  cannon = new Cannon(imageMgr);
  set = new TileSet(imageMgr, 20, 20);
}

Game::~Game() {
  delete set;
  delete cannon;
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

void Game::update() {
  cannon->update();
}

void Game::paint() {
  view.SetCenter(center);
  window->Clear(sf::Color::Black);
  set->paint(window);
  cannon->paint(window);
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
