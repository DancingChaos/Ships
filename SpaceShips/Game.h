#pragma once
#include "Player.h"
#include "Menu.h"
#include "Shop.h"
#include "Bot.h"

class Game
{
public:

  void Init();

  void InGame();
  void InMenuLoop();
  void InShopLoop();
  void GameClear();

  sf::Sprite& GetBackGroundSprite();

  std::unique_ptr <Player>& GetPlayer();

  std::unique_ptr <Menu>& GetMenu();

  std::unique_ptr <Shop>& GetShop();

  std::unique_ptr <Bot>& GetBot();

private:
  std::unique_ptr <Menu> MenuPtr;
  std::unique_ptr <Player> PlayerPtr;
  std::unique_ptr <Shop> ShopPtr;
  std::unique_ptr <Bot> BotPtr;

  sf::Texture BackGroundTexture;
  sf::Sprite BackGroundSprite;
};

