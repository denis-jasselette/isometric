#ifndef _GAME_H_
#define	_GAME_H_

#include <SFML/Graphics.hpp>
#include "imageManager.h"
#include "cursor.h"
#include "tileset.h"
#include "cannon.h"

class Game {
  public:
    Game();
    ~Game();
    void run();

  private:
    void scrollView();
    void update();
    void paint();

    void onResized(sf::Event);
    void onMouseMoved(sf::Event);
    void onKeyPressed(sf::Event);
    void onKeyReleased(sf::Event);

    sf::RenderWindow *window;
    sf::Vector2f center;
    sf::View view;
    Move::Type scroll;
    Cursor *cursor;
    ImageManager *imageMgr;
    Cannon *cannon;
    TileSet *set;
};

#endif	/* _GAME_H_ */
