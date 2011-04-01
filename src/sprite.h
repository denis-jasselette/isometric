#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "imageManager.h"

namespace Move {
    enum Type {
      NONE = 0,
      FORWARD = 1,
      BACKWARD = 1 << 1,
      TURN_CW = 1 << 2,
      TURN_CCW = 1 << 3,
      LEFT = 1 << 4,
      RIGHT = 1 << 5,
      UP = 1 << 6,
      DOWN = 1 << 7,
    };
}

class Sprite {
  public:
    Sprite(ImageManager*);
    virtual ~Sprite();
    void setPosition(sf::Vector2f);
    void setPosition(float, float);
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
