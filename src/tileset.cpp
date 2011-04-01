#include "tileset.h"

TileSet::TileSet(ImageManager *imageMgr, int width, int height) {
  this->imageMgr = imageMgr;
  this->width = width;
  this->height = height;

  set = new Tile**[height];
  for (int i = 0; i < height; i++) {
    set[i] = new Tile*[width];
    for (int j = 0; j < width; j++) {
      set[i][j] = new Tile(imageMgr);
      set[i][j]->setPosition(i, j);
    }
  }
}

TileSet::~TileSet() {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++)
      delete set[i][j];
    delete[] set[i];
  }
  delete[] set;
}

void TileSet::paint(sf::RenderWindow *window) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++)
      set[i][j]->paint(window);
  }
}
