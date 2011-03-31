#include "log.h"
#include "cannon.h"

Cannon::Cannon(ImageManager *imageMgr) {
  inMove = false;
  rotation = 0;
  frameWidth = 32;

  sf::Image *image = imageMgr->get("cannon");
  sprite = new sf::Sprite(*image);
  sprite->SetPosition(400, 300);//FIXME

  nbDirections = image->GetWidth() / frameWidth;
}

Cannon::~Cannon() {
  delete sprite;
}

void Cannon::switchMove(bool value) {
  inMove = value;
}

void Cannon::setRotation(float rotation) {
  while (rotation > 360)
    rotation -= 360;

  this->rotation = rotation;
}

void Cannon::update() {
  //setRotation(rotation + 1);
  if (inMove)
    sprite->Move(1, 0);
}

int Cannon::getIndex() {
  float directionAngle = 360.0 / nbDirections;
  return (rotation - directionAngle / 2) / directionAngle;
}

sf::IntRect Cannon::getIndexSubRect(int index) {
  index = (nbDirections - index) % nbDirections;
  int left = index * frameWidth;
  return sf::IntRect(left, 0, left + frameWidth, (int)sprite->GetSize().y);
}

sf::IntRect Cannon::getSubRect() {
  return getIndexSubRect(getIndex());
}

void Cannon::selectFrame() {
  sf::IntRect visibleRect = getSubRect();
  sprite->SetSubRect(getSubRect());
}

void Cannon::paint(sf::RenderWindow *window) {
  selectFrame();
  window->Draw(*sprite);
}
