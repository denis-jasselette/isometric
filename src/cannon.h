#ifndef _CANNON_H_
#define _CANNON_H_

#include <SFML/Graphics.hpp>
#include "sprite.h"

class Cannon : public Sprite {
  public:
    Cannon(ImageManager*, TileSet*);

    sf::Shape getBase();

  private:
    sf::Shape base;
};

#endif /* _CANNON_H_ */
