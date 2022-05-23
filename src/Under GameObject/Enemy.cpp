#include "../GameObject.h"
#include "Enemy.h"

Enemy::Enemy()
{
  speed = 350;
}
Enemy::~Enemy()
{
  if (speed != 0)
  {
    speed = 0;
  }
}
void Enemy::attack()
{

}
void Enemy::enemyMove(float dt, float direction)
{
  getSprite()->move(speed * dt * direction, 0);
}
void Enemy::getPlayer()
{

}

