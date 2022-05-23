
#ifndef PLATFORMERSFML_ENEMY_H
#define PLATFORMERSFML_ENEMY_H

#include "../GameObject.h"

class Enemy: public GameObject
{
 public:
  Enemy();
  ~Enemy();
 void enemyMove(float dt, float direction);
 void attack();
 void getPlayer(); // to target the player

 private:
  bool visible;
  int damage;
  int health;
  int speed;

};

#endif // PLATFORMERSFML_ENEMY_H
