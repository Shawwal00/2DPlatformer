
#ifndef PLATFORMERSFML_PROJECTILE_H
#define PLATFORMERSFML_PROJECTILE_H

#include "../GameObject.h"

//This is currently an unused class however I added it in case
//I had additional time

class Projectile: public GameObject
{
 public:
  Projectile();
  ~Projectile();
  void projectileMove(float dt);

 private:
  bool visible;
  int speed;
  int damage;

};


#endif // PLATFORMERSFML_PROJECTILE_H
