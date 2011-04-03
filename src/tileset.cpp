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

sf::Vector2f TileSet::convertTileToView(int x, int y) {
  int x_view = ORIG_X + TILE_WIDTH_2 * (y - x);
  int y_view = ORIG_Y + TILE_HEIGHT_2 * (y + x);
  return sf::Vector2f(x_view, y_view);
}

sf::Vector2i TileSet::convertViewToTile(float x, float y) {
  int x_set = (((int)(y - ORIG_Y)) / TILE_HEIGHT_2 - ((int)(x - ORIG_X)) / TILE_WIDTH_2) / 2;
  int y_set = (((int)(y - ORIG_Y)) / TILE_HEIGHT_2 + ((int)(x - ORIG_X)) / TILE_WIDTH_2) / 2;
  return sf::Vector2i(x_set, y_set);
}

bool TileSet::contains(sf::Vector2i tileCoords) {
  return (tileCoords.x >= 0 && tileCoords.x < width
      && tileCoords.y >= 0 && tileCoords.y < height);
}

Tile *TileSet::getTileAt(float x, float y) {
  sf::Vector2i tileCoords = convertViewToTile(x, y);

  if (contains(tileCoords))
    return set[tileCoords.x][tileCoords.y];

  return NULL;
}

void TileSet::paint(sf::RenderWindow *window) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++)
      set[i][j]->paint(window);
  }
}
