#include "game.h"
#include "log.h"

Game::Game() {
  window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Sprite test");
  cannon = new Cannon();
}

Game::~Game() {
  delete cannon;
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
  cannon->paint(window);
}

void Game::onKeyPressed(sf::Event evt) {
  log("key pressed");
}

void Game::onKeyReleased(sf::Event evt) {
  log("key released");
}
