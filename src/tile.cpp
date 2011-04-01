#include <cmath>
#include "log.h"
#include "tile.h"

#define ORIG_X 400
#define ORIG_Y   0
#define TILE_WIDTH_2  16
#define TILE_HEIGHT_2  8

Tile::Tile(ImageManager *imageMgr) : imageMgr(imageMgr) {
  sprite = new sf::Sprite();
  setImage("grass");//FIXME
}

Tile::~Tile() {
  delete sprite;
}

void Tile::setImage(std::string name) {
  sf::Image *image = imageMgr->get(name);
  sprite->SetImage(*image);
}

void Tile::setPosition(sf::Vector2i pos) {
  setPosition(pos.x, pos.y);
}

void Tile::setPosition(int x, int y) {
  int x_view = ORIG_X + TILE_WIDTH_2 * (y - x);
  int y_view = ORIG_Y + TILE_HEIGHT_2 * (y + x);
  sprite->SetPosition(x_view, y_view);
}

void Tile::paint(sf::RenderWindow *window) {
  window->Draw(*sprite);
}
