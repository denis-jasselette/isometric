#ifndef _GAME_H_
#define	_GAME_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"
#include "tileset.h"
#include "cannon.h"

class Game {
  public:
    Game();
    ~Game();
    void run();

  private:
    void update();
    void paint();

    void onKeyPressed(sf::Event);
    void onKeyReleased(sf::Event);

    sf::RenderWindow *window;
    ImageManager *imageMgr;
    Cannon *cannon;
    TileSet *set;
};

#endif	/* _GAME_H_ */
