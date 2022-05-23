
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "Under GameObject/Player.h"
#include "Under GameObject/Item.h"
#include "Under GameObject/Enemy.h"
#include "Under GameObject/Projectile.h"
#include "Under GameObject/Tile.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event, float dt);
  void keyReleased(sf::Event event);
  void tilePlacement();
  void coinPlacement();
  void reset();
  void playerMovement(float dt);
  void enemyMovement(float dt);

 private:
  sf::RenderWindow& window;
  sf::Sprite sprite;

  //Textures
  sf::Texture player_texture;
  sf::Texture tile_texture;
  sf::Texture enemy_texture;
  sf::Texture projectile_texture;
  sf::Texture background_texture;
  sf::Texture coin_texture;

  //Text
  sf::Text enter_text;
  sf::Text win_text;
  sf::Text lose_text;
  sf::Text pause_text;
  sf::Text score_text;
  sf::Text lives_text;
  sf::Font font;

  //Ints
  int score = 0;
  int top_tiles_not_touched = 0;
  int tiles_touched = 0;
  int coins_left = 10;

  //Other Classes
  Player player;
  Enemy enemy[2];
  Projectile projectile[5];
  Item items [10];
  Tile tiles[50];
  GameObject background;

  //Bools
  bool left = false;
  bool right = false;
  bool fall = false;
  bool jump = false;
  bool inside_tile = false;

  //float
  float jump_y = 0;
  float enemy_direction = -1;

  //Time
  sf::Time jump_time;
  sf::Clock jump_clock;

  enum class GameState : int
  {
    MENU = 0,
    PLAY = 1,
    GAME_OVER = 2,
    PAUSE = 3,
    WIN = 4
  };

  GameState game_state = GameState::MENU;

};

#endif // PLATFORMER_GAME_H
