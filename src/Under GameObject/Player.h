

#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H

#include "../GameObject.h"

class Player: public GameObject
{
 public:
  Player();
  ~Player();
  void playerMove(float dt);
  void gravity(float dt);
  void jump(float dt, float velocity_y);
  bool die();
  bool topTileCollider(sf::Sprite* one, sf::Sprite* two);
  bool restOfTileCollider(sf::Sprite* one, sf::Sprite* two);
  bool enemyCollider(sf::Sprite* one, sf::Sprite* two);
  void loseLife();
  int returnLife();
  void resetLife();// for the restart

 private:
  int speed;
  int lives;
  int gravity_speed;

};
#endif // PLATFORMERSFML_PLAYER_H
