#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "GraphSystem.h"
#include "GameManager.h"


int main()
{ 
  GraphSystem::Init();
  GameManager::GetGame()->Init();

  while (GameSettings::GetWindow().isOpen())
  {
    sf::Event event;
    while (GameSettings::GetWindow().pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        GameSettings::GetWindow().close();

      if (GameSettings::GetState() == MainMenu)
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
          GameManager::GetGame()->GetMenu()->Click();

      if (GameSettings::GetState() == Shoping)
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
          GameManager::GetGame()->GetShop()->Click();

      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && GameSettings::GetState() == Playing)
        GameManager::GetGame()->GetPlayer()->SelectShip();

      if (GameSettings::GetState() == Playing)
      {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
          GameManager::GetGame()->GetPlayer()->SelectShip();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
          GameManager::GetGame()->GetPlayer()->SetEnemyShip();
      }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && GameSettings::GetState() == Playing)
        GameManager::GetGame()->GetPlayer()->MoveShip();
    }

    GameSettings::GetWindow().clear();

    GameSettings::GetWindow().draw(GameManager::GetGame()->GetBackGroundSprite());

    if (GameSettings::GetState() == MainMenu)
      GameManager::GetGame()->InMenuLoop();
    if (GameSettings::GetState() == Playing)
      GameManager::GetGame()->InGame();
    if (GameSettings::GetState() == Shoping)
      GameManager::GetGame()->InShopLoop();


    GameSettings::GetWindow().display();
  }
  return 0;
}