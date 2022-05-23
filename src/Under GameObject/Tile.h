

#ifndef PLATFORMERSFML_TILE_H
#define PLATFORMERSFML_TILE_H

#include "../GameObject.h"


class Tile: public GameObject
{
 public:
  Tile();
  ~Tile();
  void placeTile(int x, int y);

 private:

};
#endif // PLATFORMERSFML_TILE_H
