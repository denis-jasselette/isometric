#include "game.h"
#include "log.h"

/* FIXME: clean up */
#define SET_HEIGHT 20
#define SET_WIDTH 20

Game::Game() {
  window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Sprite test");
  imageMgr = new ImageManager();
  cannon = new Cannon(imageMgr);

  set = new Tile**[SET_HEIGHT];
  for (int i = 0; i < SET_HEIGHT; i++) {
    set[i] = new Tile*[SET_WIDTH];
    for (int j = 0; j < SET_WIDTH; j++) {
      set[i][j] = new Tile(imageMgr);
      set[i][j]->setPosition(i, j);
    }
  }
}

Game::~Game() {
  for (int i = 0; i < SET_HEIGHT; i++) {
    for (int j = 0; j < SET_WIDTH; j++)
      delete set[i][j];
    delete[] set[i];
  }
  delete[] set;

  delete cannon;
  delete imageMgr;
  delete window;
}

void Game::run() {
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
  window->Clear(sf::Color::White);

  for (int i = 0; i < SET_HEIGHT; i++) {
    for (int j = 0; j < SET_WIDTH; j++)
      set[i][j]->paint(window);
  }

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
