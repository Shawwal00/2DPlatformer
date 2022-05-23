#include "../GameObject.h"
#include "Tile.h"

Tile::Tile()
{

}
Tile::~Tile()
{

}

void Tile::placeTile(int x , int y)
{

  getSprite()->setPosition(x,y);
  getSprite()->setScale(5,5);
}



