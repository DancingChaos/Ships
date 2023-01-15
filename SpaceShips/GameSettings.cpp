#include "GameSettings.h"

sf::View GameSettings::GameView = sf::View(sf::FloatRect(0, 0, 1600, 960));

sf::RenderWindow GameSettings::Window = sf::RenderWindow(sf::VideoMode((size_t)GameSettings::GetView().getSize().x, (size_t)GameSettings::GetView().getSize().y), "SFML works!");

State GameSettings::MenuState = MainMenu;

bool GameSettings::IsGameStarted = false;
bool GameSettings::IsPaused = false;

int GameSettings::PlayerAttackersCount = 0;
int GameSettings::PlayerCommanderCount = 0;
int GameSettings::PlayerDefenderCount = 0;
int GameSettings::PlayerSupportCount = 0;
int GameSettings::PlayerCaravanCount = 0;

int GameSettings::BotAttackersCount = 0;
int GameSettings::BotCommanderCount = 0;
int GameSettings::BotDefenderCount = 0;
int GameSettings::BotSupportCount = 0;
int GameSettings::BotCaravanCount = 0;


void GameSettings::BotFleetCountClear()
{
  BotAttackersCount = 0;
  BotCommanderCount = 0;
  BotDefenderCount = 0;
  BotSupportCount = 0;
  BotCaravanCount = 0;
}

bool GameSettings::IsEven(const int Num)
{
  return Num % 2 == 0 ? true : false;
}

void GameSettings::SetState(State NewMenuState)
{
  MenuState = NewMenuState;
}

State GameSettings::GetState()
{
  return MenuState;
}

sf::View& GameSettings::GetView()
{
  return GameView;
}

sf::Vector2f GameSettings::GetMousePos()
{
  return sf::Vector2f(sf::Mouse::getPosition(Window));
}

sf::RenderWindow& GameSettings::GetWindow()
{
  return Window;
}