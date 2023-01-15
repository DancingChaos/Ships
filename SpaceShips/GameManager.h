#pragma once
#include "Game.h"

class GameManager
{
public:
  static std::unique_ptr<Game> & GetGame();
private:
  static std::unique_ptr<Game> GamePtr;
};

