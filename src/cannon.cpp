#include <cmath>
#include "log.h"
#include "cannon.h"

Cannon::Cannon(ImageManager *imageMgr) : Sprite(imageMgr) {
  setImage("cannon");
}

Cannon::~Cannon() {
}

void Cannon::update() {
  Sprite::update();
}

void Cannon::paint(sf::RenderWindow *window) {
  Sprite::paint(window);
}
