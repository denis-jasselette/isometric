#ifndef _CANNON_H_
#define _CANNON_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"

namespace Move {
    enum Type {
      NONE = 0, FORWARD = 1, BACKWARD = 2, TURN_CW = 4, TURN_CCW = 8
    };
}

class Cannon {
  public:
    Cannon(ImageManager*);
    ~Cannon();
    Move::Type getMove();
    void setMove(Move::Type);
    void update();
    void paint(sf::RenderWindow*);

  private:
    float clampAngle(float);
    void setRotation(float);
    int getIndex();
    sf::IntRect getIndexSubRect(int);
    sf::IntRect getSubRect();
    void selectFrame();

    Move::Type move;
    float rotation;
    int frameWidth;
    int nbDirections;
    sf::Sprite *sprite;
};

#endif /* _CANNON_H_ */
