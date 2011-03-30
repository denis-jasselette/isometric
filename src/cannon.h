#ifndef _CANNON_H_
#define _CANNON_H_

#include <SFML/Graphics.hpp>

class Cannon {
  public:
    Cannon();
    ~Cannon();
    void update();
    void paint(sf::RenderWindow*);

  private:
    void setRotation(float);
    int getIndex();
    sf::IntRect getIndexSubRect(int);
    sf::IntRect getSubRect();
    void selectFrame();

    float rotation;
    int frameWidth;
    int nbDirections;
    sf::Sprite *sprite;
};

#endif /* _CANNON_H_ */
