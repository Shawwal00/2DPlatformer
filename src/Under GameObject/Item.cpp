#include "../GameObject.h"
#include "Item.h"

Item::Item()
{
  score = 0;
}
Item::~Item()
{
  if (score != 0)
  {
    score = 0;
  }
}
void Item::relocate()
{

}
int Item::addScore()
{
  score = score + 100;
  return score;
}
bool Item::checkVisibility()
{
  if (visible == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Item::changeVisibility()
{
  visible = !visible;
}

void Item::resetVisibility()
{
  visible = true;
}
void Item::resetScore()
{
  score = 0;
}