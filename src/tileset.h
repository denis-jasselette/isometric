#ifndef _TILESET_H_
#define _TILESET_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"
#include "tile.h"

class TileSet {
  public:
    TileSet(ImageManager*, int width, int height);
    ~TileSet();

    sf::Vector2f convertTileToView(int, int);
    sf::Vector2i convertViewToTile(float, float);
    bool contains(sf::Vector2i);
    Tile *getTileAt(float x, float y);
    void paint(sf::RenderWindow *window);

  private:
    int width, height;
    ImageManager *imageMgr;
    Tile ***set;
};

#endif /* _TILESET_H_ */
