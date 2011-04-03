#include <cmath>
#include "log.h"
#include "cannon.h"

sf::Shape getTileShape(sf::Vector2i center, int width) {
  int height = width / 2;
  sf::Shape s;
  s.AddPoint(center.x, center.y - height / 2);
  s.AddPoint(center.x + width / 2, center.y);
  s.AddPoint(center.x, center.y + height / 2);
  s.AddPoint(center.x - width / 2, center.y);

  return s;
}

Cannon::Cannon(ImageManager *imageMgr, TileSet *tileset) : Sprite(imageMgr, tileset) {
  setImage("cannon");
}

sf::Shape Cannon::getBase() {
  base = getTileShape(getAbsoluteCenter(), frameWidth);
  base.EnableFill(false);
  base.EnableOutline(true);
  base.SetOutlineWidth(1);
  for (int i = base.GetNbPoints() - 1; i >= 0; i--)
    base.SetPointOutlineColor(i, sf::Color::Green);

  return base;
}
