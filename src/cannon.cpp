#include "log.h"
#include "cannon.h"

#define RES(f) "./res/" f

Cannon::Cannon() {
  rotation = 0;
  frameWidth = 32;

  sf::Image *image = new sf::Image();//TODO: replace with ImageManager
  if (!image->LoadFromFile(RES("cannon.png"))) {
    log("Error: Loading of `cannon.png' failed");
  }

  sprite = new sf::Sprite(*image);

  nbDirections = image->GetWidth() / frameWidth;
}

Cannon::~Cannon() {
  delete sprite->GetImage();
  delete sprite;
}

void Cannon::setRotation(float rotation) {
  while (rotation > 360)
    rotation -= 360;

  this->rotation = rotation;
}

void Cannon::update() {
  setRotation(rotation + 1);
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
  /*sprite->SetCenter(visibleRect.Left + visibleRect.GetWidth() / 2,
      visibleRect.Top + visibleRect.GetHeight() / 2);*/
  sprite->SetSubRect(getSubRect());
}

void Cannon::paint(sf::RenderWindow *window) {
  selectFrame();
  sprite->SetPosition(window->GetWidth() / 2, window->GetHeight() / 2);
  window->Draw(*sprite);
}
