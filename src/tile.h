#ifndef _TILE_H_
#define _TILE_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "sprite.h"//FIXME: factorize Move
#include "imageManager.h"

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
