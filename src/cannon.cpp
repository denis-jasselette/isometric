#include <cmath>
#include "log.h"
#include "cannon.h"

Cannon::Cannon(ImageManager *imageMgr) {
  move = Move::NONE;
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

Move::Type Cannon::getMove() {
  return move;
}

void Cannon::setMove(Move::Type type) {
  move = type;
}

void Cannon::setRotation(float rotation) {
  this->rotation = clampAngle(rotation);
}

float Cannon::clampAngle(float angle) {
  while (angle < 0)
    angle += 360;

  return fmod(angle, 360);
}

void Cannon::update() {
  if (move & Move::TURN_CCW)
    setRotation(rotation + 1);
  if (move & Move::TURN_CW)
    setRotation(rotation - 1);

  int direction = 0;
  if (move & Move::FORWARD)
    direction++;
  if (move & Move::BACKWARD)
    direction--;

  if (direction == 0)
    return;

  float angle = (direction > 0)? rotation : rotation + 180;
  float rad_angle = M_PI * angle / 180;
  sprite->Move(cos(rad_angle), -sin(rad_angle));
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
