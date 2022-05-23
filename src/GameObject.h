#include "iostream"
#include <SFML//Graphics.hpp>


#ifndef PLATFORMERSFML_GAMEOBJECT_H
#define PLATFORMERSFML_GAMEOBJECT_H
class GameObject
{
 public:
  GameObject();
  ~GameObject();
  bool initialiseSprite(sf::Texture& texture, std::string filename);
  sf::Sprite* getSprite();
  bool collider(sf::Sprite* one, sf::Sprite* two);
 protected:


 private:
  sf::Sprite* sprite = nullptr;

};
#endif // PLATFORMERSFML_GAMEOBJECT_H
