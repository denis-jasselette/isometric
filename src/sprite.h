#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "imageManager.h"
#include "tileset.h"
#include "move.h"

class Sprite {
  public:
    Sprite(ImageManager*, TileSet*);
    virtual ~Sprite();

    void setPosition(sf::Vector2f);
    void setPosition(float, float);
    void translate(float, float);
    Move::Type getMove();
    void setMove(Move::Type);
    bool isMoving(Move::Type);
    sf::Vector2i getAbsoluteCenter();
    virtual void update(float delta);
    virtual void paint(sf::RenderWindow*);

  protected:
    void setImage(std::string);
    void setRotation(float);
    virtual sf::Shape getBase() = 0;

    ImageManager *imageMgr;
    TileSet *tileset;
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
