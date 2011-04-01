#ifndef _TILESET_H_
#define _TILESET_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"
#include "tile.h"

class TileSet {
  public:
    TileSet(ImageManager*, int width, int height);
    ~TileSet();

    void paint(sf::RenderWindow *window);

  private:
    int width, height;
    ImageManager *imageMgr;
    Tile ***set;
};

#endif /* _TILESET_H_ */
