
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{

if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
{
  std::cout << "font did not load \n";
}
enter_text.setString("This is a platformer game, use A and D \n"
                     "to move left or right and use SPACE to jump,\n"
                     "Press P to Pause\n"
                     "press enter to start ");
enter_text.setFont(font);
enter_text.setCharacterSize(40);
enter_text.setFillColor(sf::Color(0, 0, 0, 255));
enter_text.setPosition(75, 50);
enter_text.setScale(1,1);

win_text.setString("You have won, press R to play again");
win_text.setFont(font);
win_text.setCharacterSize(40);
win_text.setFillColor(sf::Color(0, 0, 0, 255));
win_text.setPosition(75, 50);
win_text.setScale(1,1);

lose_text.setString("You have lost, press R to play again");
lose_text.setFont(font);
lose_text.setCharacterSize(40);
lose_text.setFillColor(sf::Color(0, 0, 0, 255));
lose_text.setPosition(75, 50);
lose_text.setScale(1,1);

pause_text.setString("You have paused the game, press P to unpause");
pause_text.setFont(font);
pause_text.setCharacterSize(40);
pause_text.setFillColor(sf::Color(0, 0, 0, 255));
pause_text.setPosition(75, 50);
pause_text.setScale(1,1);

score_text.setFont(font);
score_text.setCharacterSize(40);
score_text.setFillColor(sf::Color(0, 0, 0, 255));
score_text.setPosition(775, 10);
score_text.setScale(1,1);

lives_text.setFont(font);
lives_text.setCharacterSize(40);
lives_text.setFillColor(sf::Color(0, 0, 0, 255));
lives_text.setPosition(20, 10);
lives_text.setScale(1,1);

player.initialiseSprite(player_texture, "Data/Images/kenney_tooncharacters1/"
                                        "Robot/Poses/character_robot_idle.png");
player.getSprite()->setPosition(20,500);
player.getSprite()->setScale(1,1);

int enemy_X = 600;
int enemy_y = 570;
for (int i = 0; i < 2; ++i)
{
   enemy[i].initialiseSprite(enemy_texture, "Data/Images/kenney_"
                                           "pixelplatformer/Characters/"
                                           "character_0006.png");
   enemy[i].getSprite()->setPosition(enemy_X,enemy_y);
   enemy[i].getSprite()->setScale(3,3);
   enemy_X = enemy_X - 100;
   enemy_y = enemy_y - 200;
}

background.initialiseSprite(background_texture,"Data/Images/kenney_pixelplatfor"
                                                "mer/Background/background_mi"
                                                "ddle.png");
background.getSprite()->setPosition(0,0);
background.getSprite()->setScale(45,45);

tilePlacement(); //generates tiles
coinPlacement(); //generates coins

  return true;
}

void Game::update(float dt)
{
jump_time = jump_clock.getElapsedTime();
score_text.setString("Score = " + std::to_string(score) );
lives_text.setString("Lives = " + std::to_string(player.returnLife()));


  if (game_state == GameState::PLAY)
  {
    enemyMovement(dt);
    playerMovement(dt);
  }
  for (int i = 0; i < 10; ++i) // responsible for the coins
  {
    if (items[i].checkVisibility())
    {
      if (player.collider(player.getSprite(), items[i].getSprite()))
      {
        items[i].changeVisibility();
        coins_left = coins_left - 1;
        score = items->addScore();
      }
    }
  }
  if (coins_left == 0)
  {
    game_state = GameState::WIN;
  }
}

void Game::render()
{
  window.draw(*background.getSprite());
  if (game_state == GameState::MENU)
  {
    window.draw(enter_text);
  }
  else if (game_state == GameState::PLAY)
  {
    window.draw(score_text);
    window.draw(lives_text);
    window.draw(*player.getSprite());
    for (int i = 0; i < 2; ++i)
    {
      window.draw(*enemy[i].getSprite());
    }
    for (int i = 0; i < 20; ++i)
    {
      window.draw(*tiles[i].getSprite());
    }
    for (int i = 0; i < 10; ++i)
    {
     if(items[i].checkVisibility())
     {
       window.draw(*items[i].getSprite());
     }
    }
  }
  else if (game_state == GameState::WIN)
  {
    window.draw(win_text);
  }

  else if (game_state == GameState::GAME_OVER)
  {
    window.draw(lose_text);
  }

  else if (game_state == GameState::PAUSE)
  {
    window.draw(pause_text);
  }

}

void Game::mouseClicked(sf::Event event) // Unused
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event, float dt)
{
  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
  }
  if (game_state == GameState::MENU)
  {
    if (event.key.code == sf::Keyboard::Enter)
    {
      game_state = GameState::PLAY;
    }
  }

  if (game_state == GameState::PLAY)
  {
    if (event.key.code == sf::Keyboard::A)
    {
      left = true;
    }
    if (event.key.code == sf::Keyboard::D)
    {
      right = true;
    }
    if (event.key.code == sf::Keyboard::Space)
    {
      if(jump == false && fall == false)
      {
        jump_clock.restart();
        jump_y = 15;
        jump = true;
      }
    }

    }
    if (game_state == GameState::PLAY || game_state == GameState::PAUSE)
    {
    if (event.key.code == sf::Keyboard::P)
    {
      if (game_state == GameState::PLAY)
      {
        game_state = GameState::PAUSE;
      }
      else if (game_state == GameState::PAUSE)
      {
        game_state = GameState::PLAY;
      }
    }
  }
  if(game_state == GameState::GAME_OVER || game_state == GameState::WIN)
  {
    if (event.key.code == sf::Keyboard::R)
    {
      reset();
    }
  }

}

void Game::keyReleased(sf::Event event)
{
  if (game_state == GameState::PLAY)
  {
    if (event.key.code == sf::Keyboard::A)
    {
      left = false;
    }
    if (event.key.code == sf::Keyboard::D)
    {
      right = false;
    }
    if (event.key.code == sf::Keyboard::Space)
    {
      jump = false;
    }
  }
}

void Game::tilePlacement()
{
  int first_layer_x = 0;
  int first_layer_y = 635;
  for (int i = 0; i < 20; ++i)
  {
    tiles[i].initialiseSprite(tile_texture,"Data/Images/kenney_pixelplatformer/"
                                            "Tiles/tile_0006.png" );
    tiles[i].placeTile(first_layer_x,first_layer_y);

    if(i < 11)
    {
      first_layer_x =
        first_layer_x + tiles[0].getSprite()->getTexture()->getSize().x *
                          tiles[0].getSprite()->getScale().x;
    }
    else if (i == 11)
    {
      first_layer_x = 400;
      first_layer_y =
        first_layer_y - player.getSprite()->getTexture()->getSize().y * 1.5;
    }
    else if (i > 11 && i < 16)
    {
      first_layer_x =  first_layer_x + tiles[0].getSprite()->getTexture()->
                                        getSize().x * tiles[0].getSprite()->
                                        getScale().x;
    }
    else if (i == 16)
    {
      first_layer_x = 100;
      first_layer_y = first_layer_y - player.getSprite()->getTexture()
                                          ->getSize().y * 1.4;
    }
    else if (i > 16)
    {
      first_layer_x =  first_layer_x + tiles[0].getSprite()->getTexture()->
                                        getSize().x * tiles[0].getSprite()->
                                        getScale().x;
    }
  }
}

void Game::coinPlacement()
{
  int x = 450;
  int y = 580;
  for (int i = 0; i < 10; ++i)
  {
    items[i].initialiseSprite(coin_texture, "Data/Images/kenney_physicspack/PN"
                                            "G/Other/coinGold.png");
    items[i].getSprite()->setPosition(x,y);
    items[i].getSprite()->setScale(1,1);

    if (i < 3)
    {
      x = x + 100;
    }
    if (i == 3)
    {
      y = 380;
    }
    if(i > 3 && i < 7)
    {
      x = x -100;
    }
    if(i == 7)
    {
      y = 200;
      x = x -200;
    }
    if(i > 7)
    {
      x = x -100;
    }
  }
}

void Game::reset()
{
  player.getSprite()->setPosition(100,100);
  player.resetLife();
  game_state = GameState::PLAY;
  items->resetScore();
  coins_left = 10;
  left = false;
  right = false;
  fall = false;
  jump = false;
  for (int i = 0; i < 10; ++i)
  {
    items[i].resetVisibility();
  }
}

void Game::playerMovement(float dt)
{
  if(player.die())
  {
    game_state = GameState::GAME_OVER;
  }
  if (left == true && player.getSprite()->getPosition().x > 0 &&
      inside_tile == false)
  {
    player.playerMove(-dt);
  }
  else if (right == true && player.getSprite()->getPosition().x <
                              window.getSize().x - player.getSprite()->
                                                   getGlobalBounds().width &&
           inside_tile == false)
  {
    player.playerMove(dt);
  }

  if (fall == true && jump == false)
  {
    player.gravity(dt);
  }

  if(jump == true && inside_tile == false && player.getSprite()
                                                  ->getPosition().y > -20)
  {
    player.jump(dt, jump_y);
  }
  if (jump_time.asSeconds() > 0.23)
  {
    fall = true;
    jump = false;
  }
  for (int i = 0; i < 20; ++i)
  {
    if (i == 19)
    {
      top_tiles_not_touched = 0;
      tiles_touched = 0;
    }
    if (!player.topTileCollider(player.getSprite(), tiles[i].getSprite()))
    {
      top_tiles_not_touched = top_tiles_not_touched + 1;

      if(top_tiles_not_touched == 20)
      {
        fall = true;
      }
    }
    else
    {
      fall = false;
    }
    if (player.restOfTileCollider(player.getSprite(), tiles[i].getSprite()))
    {
      inside_tile = true;
    }
    else
    {
      tiles_touched = tiles_touched + 1;
      if (tiles_touched == 20)
      {
        inside_tile = false;
      }
    }
  }
}

void Game::enemyMovement(float dt)
{
  for (int i = 0; i < 2; ++i)
  {
    if(player.enemyCollider(player.getSprite(), enemy[i].getSprite()))
    {
      player.loseLife();
    }
    enemy[i].enemyMove(dt,enemy_direction);
    if(enemy[i].getSprite()->getPosition().x < 0)
    {
      enemy_direction = enemy_direction * -1;
    }
    else if (enemy[i].getSprite()->getPosition().x >
             window.getSize().x -enemy[i].getSprite()->getGlobalBounds().width)
    {
      enemy_direction = enemy_direction * -1;
    }
  }
}






