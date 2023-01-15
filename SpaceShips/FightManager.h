#pragma once
#include "User.h"

class FightManager
{
public:
  bool IsGameOver(User & FirstPlayer, User & SecondPlayer);
  void Update();
private:
};

