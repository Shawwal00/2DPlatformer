#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "iostream"

GameObject::GameObject()
{
  sprite = new sf::Sprite();
}
GameObject::~GameObject()
{
  if (sprite != nullptr)
  {
    delete sprite;
    sprite = nullptr;
  }
}
bool GameObject::initialiseSprite(sf::Texture&texture, std::string filename)
{
  if (!texture.loadFromFile(filename))
  {
    std::cout << "texture did not load \n";
  }
  sprite->setTexture(texture);
  return false;
}

sf::Sprite* GameObject::getSprite()
{
  return sprite;
}
bool GameObject::collider(sf::Sprite* one, sf::Sprite* two)
{
  if (
    one->getPosition().x < two->getPosition().x + two->getGlobalBounds().width
    &&
    one->getPosition().x + one->getGlobalBounds().width > two->getPosition().x
    &&
    one->getPosition().y < two->getPosition().y + two->getGlobalBounds().height
    &&
    one->getPosition().y + one->getGlobalBounds().height > two->getPosition().y)
    {
   return true;
    }
 else
 {
   return false;
 }
}
