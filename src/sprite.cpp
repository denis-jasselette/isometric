#include <cmath>
#include "log.h"
#include "sprite.h"

Sprite::Sprite(ImageManager *imageMgr, TileSet *tileset) {
  this->imageMgr = imageMgr;
  this->tileset = tileset;

  move = Move::NONE;
  rotation = 0;
  frameWidth = 32;

  sprite = new sf::Sprite();
  sprite->SetPosition(400, 300);//FIXME
  sprite->SetCenter(frameWidth / 2, frameWidth / 2);
  nbDirections = 1;
}

Sprite::~Sprite() {
  delete sprite;
}

void Sprite::setImage(std::string name) {
  sf::Image *image = imageMgr->get(name);
  sprite->SetImage(*image);
  nbDirections = image->GetWidth() / frameWidth;
}

void Sprite::setPosition(sf::Vector2f pos) {
  setPosition(pos.x, pos.y);
}

void Sprite::setPosition(float x, float y) {
  sprite->SetPosition(x, y);
}

void Sprite::translate(float x, float y) {
  setPosition(sprite->GetPosition() + sf::Vector2f(x, y));
}

Move::Type Sprite::getMove() {
  return move;
}

void Sprite::setMove(Move::Type type) {
  move = type;
}

bool Sprite::isMoving(Move::Type direction) {
  return move & direction;
}

void Sprite::setRotation(float rotation) {
  this->rotation = clampAngle(rotation);
}

float Sprite::clampAngle(float angle) {
  while (angle < 0)
    angle += 360;

  return fmod(angle, 360);
}

sf::Vector2i Sprite::getAbsoluteCenter() {
  sf::Vector2f absCenter = sprite->GetPosition();
  return sf::Vector2i(absCenter.x, absCenter.y);
}

void Sprite::update() {
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
  translate(cos(rad_angle), -sin(rad_angle));
}

int Sprite::getIndex() {
  float directionAngle = 360.0 / nbDirections;
  return (rotation - directionAngle / 2) / directionAngle;
}

sf::IntRect Sprite::getIndexSubRect(int index) {
  index = (nbDirections - index - 1) % nbDirections;
  int left = index * frameWidth;
  return sf::IntRect(left, 0, left + frameWidth, (int)sprite->GetSize().y);
}

sf::IntRect Sprite::getSubRect() {
  return getIndexSubRect(getIndex());
}

void Sprite::selectFrame() {
  sf::IntRect visibleRect = getSubRect();
  sprite->SetSubRect(getSubRect());
}

void Sprite::paint(sf::RenderWindow *window) {
  window->Draw(getBase());
  selectFrame();
  window->Draw(*sprite);
}
