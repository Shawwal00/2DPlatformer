
#ifndef PLATFORMERSFML_ITEM_H
#define PLATFORMERSFML_ITEM_H

#include "../GameObject.h"

class Item: public GameObject
{
 public:
  Item();
  ~Item();
  int addScore();
  void relocate();
  void resetScore();
  bool checkVisibility();
  void changeVisibility();
  void resetVisibility();

 private:
  bool visible = true;
  int score;
};

#endif // PLATFORMERSFML_ITEM_H
