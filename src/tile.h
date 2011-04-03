#ifndef _TILE_H_
#define _TILE_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "move.h"
#include "imageManager.h"

#define ORIG_X 400
#define ORIG_Y   0
#define TILE_WIDTH_2  16
#define TILE_HEIGHT_2  8

class Tile {
  public:
    Tile(ImageManager*);
    virtual ~Tile();
    void setPosition(sf::Vector2i);
    void setPosition(int, int);
    virtual void paint(sf::RenderWindow*);

  protected:
    void setImage(std::string);

    ImageManager *imageMgr;
    sf::Sprite *sprite;
};

#endif /* _TILE_H_ */
