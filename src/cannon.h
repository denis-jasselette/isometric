#ifndef _CANNON_H_
#define _CANNON_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"
#include "sprite.h"

class Cannon : public Sprite {
  public:
    Cannon(ImageManager*);
    ~Cannon();
    void update();
    void paint(sf::RenderWindow*);
};

#endif /* _CANNON_H_ */
