#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "imageManager.h"

namespace Move {
    enum Type {
      NONE = 0, FORWARD = 1, BACKWARD = 2, TURN_CW = 4, TURN_CCW = 8
    };
}

class Sprite {
  public:
    Sprite(ImageManager*);
    virtual ~Sprite();
    Move::Type getMove();
    void setMove(Move::Type);
    bool isMoving(Move::Type);
    virtual void update();
    virtual void paint(sf::RenderWindow*);

  protected:
    void setImage(std::string);
    void setRotation(float);

    ImageManager *imageMgr;
    Move::Type move;
    float rotation;
    int frameWidth;
    int nbDirections;
    sf::Sprite *sprite;

  private:
    float clampAngle(float);
    int getIndex();
    sf::IntRect getIndexSubRect(int);
    sf::IntRect getSubRect();
    void selectFrame();
};

#endif /* _SPRITE_H_ */
