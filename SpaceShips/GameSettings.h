#pragma once
#include <SFML/Graphics.hpp>

  enum State
  {
    MainMenu,
    Playing,
    Shoping
  };



class GameSettings
{
public:

  static sf::View& GetView();
  static sf::Vector2f GetMousePos();
  static sf::RenderWindow& GetWindow();
  static State GetState();
  static void SetState(State MenuState);
  static void BotFleetCountClear();
  static bool IsEven(const int Num);

  static int PlayerAttackersCount;
  static int PlayerSupportCount;
  static int PlayerDefenderCount;
  static int PlayerCaravanCount;
  static int PlayerCommanderCount;

  static int BotAttackersCount;
  static int BotCommanderCount;
  static int BotDefenderCount;
  static int BotSupportCount;
  static int BotCaravanCount;

  static const int ATTACKERS_LIMIT = 6;
  static const int DEFENDER_LIMIT  = 4;
  static const int CARAVAN_LIMIT   = 2;
  static const int COMMANDER_LIMIT = 1;
  static const int SUPPORT_LIMIT   = 4;
private:
  static bool IsPaused;
  static bool IsGameStarted;


  static State MenuState;

  static sf::View GameView;
  static sf::RenderWindow Window;
};
