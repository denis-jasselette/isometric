#ifndef _CANNON_H_
#define _CANNON_H_

#include <SFML/Graphics.hpp>
#include "sprite.h"

class Cannon : public Sprite {
  public:
    Cannon(ImageManager*, TileSet*);
    ~Cannon();
    void update();
    void paint(sf::RenderWindow*);
};

#endif /* _CANNON_H_ */
