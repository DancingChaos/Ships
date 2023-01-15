#include "Game.h"
#include <iostream>

void Game::Init()
{
  if (!BackGroundTexture.loadFromFile("..\\Images\\BackGround.png"))
    std::cout << "Failed to load from file!";
  else
  {
    BackGroundSprite.setTexture(BackGroundTexture);
    BackGroundSprite.setPosition(0.f, 0.f);
  }
  MenuPtr   = std::make_unique<Menu>();
  PlayerPtr = std::make_unique<Player>();
  ShopPtr   = std::make_unique<Shop>();
  BotPtr    = std::make_unique<Bot>();

  ShopPtr->Init();
  MenuPtr->Init();
}

void Game::GameClear()
{
  BotPtr->GetFleet().clear();
  GameSettings::BotFleetCountClear();
}

void Game::InGame()
{
  if (PlayerPtr->GetFleet().empty() || BotPtr->GetFleet().empty())
  {
     GameClear();

     GameSettings::SetState(MainMenu);
  }

  GraphSystem::Draw();

  PlayerPtr->DrawFleet();
  PlayerPtr->Update();

  BotPtr->DrawFleet();
  BotPtr->Update();
}

void Game::InMenuLoop()
{
  MenuPtr->Draw();
}

void Game::InShopLoop()
{
  ShopPtr->Update();
  ShopPtr->Draw();
}

sf::Sprite& Game::GetBackGroundSprite()
{
  return BackGroundSprite;
}

std::unique_ptr <Player>& Game::GetPlayer()
{
  return PlayerPtr;
}

std::unique_ptr <Menu>& Game::GetMenu()
{
  return MenuPtr;
}

std::unique_ptr <Shop>& Game::GetShop()
{
  return ShopPtr;
}

std::unique_ptr <Bot>& Game::GetBot()
{
  return BotPtr;
}
