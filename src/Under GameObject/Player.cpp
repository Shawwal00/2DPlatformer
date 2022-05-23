#include "Player.h"
#include "../GameObject.h"

Player::Player()
{
  speed = 350;
  gravity_speed = 350;
  lives = 3;
}
Player::~Player()
{
  if (speed != 0)
  {
    speed = 0;
  }

  if (gravity_speed != 0)
  {
    gravity_speed = 0;
  }

  if(lives != 0)
  {
    lives = 0;
  }

}
void Player::playerMove(float dt)
{
  getSprite()->move(speed * dt, 0);
}

void  Player::gravity(float dt)
{
  getSprite()->move(0,  dt * gravity_speed);
}

void  Player::jump(float dt, float velocity_y)
{
  float current_x = getSprite()->getPosition().x;
  float current_y = getSprite()->getPosition().y;
  getSprite()->setPosition(current_x,  current_y - velocity_y );

}

bool Player::die()
{
  if (lives <= 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Player::loseLife()
{
  lives = lives - 1;
  getSprite()->setPosition(100, 100);
}

void Player::resetLife()
{
  lives = 3;
}

int Player::returnLife()
{
  return lives;
}

bool Player::topTileCollider(sf::Sprite* player, sf::Sprite* tile)
{
  if (
    player->getPosition().x <
      tile->getPosition().x + tile->getGlobalBounds().width &&
    player->getPosition().x + player->getGlobalBounds().width >
      tile->getPosition().x &&
    player->getPosition().y + 205 <
      tile->getPosition().y + tile->getGlobalBounds().height &&
    player->getPosition().y + player->getGlobalBounds().height >
      tile->getPosition().y)
  {
    return true;
  }
  else
  {
    return false;
  }
}
bool Player::restOfTileCollider(sf::Sprite* player, sf::Sprite* tile)
{
  if (
    player->getPosition().x <
      tile->getPosition().x + tile->getGlobalBounds().width &&
    player->getPosition().x + player->getGlobalBounds().width >
      tile->getPosition().x &&
    player->getPosition().y + 50 <
      tile->getPosition().y + tile->getGlobalBounds().height &&
    player->getPosition().y + player->getGlobalBounds().height >
      tile->getPosition().y + 50)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Player::enemyCollider(sf::Sprite* player, sf::Sprite* enemy)
{
  if (
    player->getPosition().x <
      enemy->getPosition().x + enemy->getGlobalBounds().width - 75 &&
    player->getPosition().x + player->getGlobalBounds().width >
      enemy->getPosition().x + 40 &&
    player->getPosition().y <
      enemy->getPosition().y + enemy->getGlobalBounds().height &&
    player->getPosition().y + player->getGlobalBounds().height >
      enemy->getPosition().y)
  {
    return true;
  }
  else
  {
    return false;
  }
}
