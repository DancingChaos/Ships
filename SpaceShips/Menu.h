#pragma once
#include "Button.h"
#include "GameSettings.h"
#include "Shop.h"

class Menu
{
public:
  void Update();
  void Draw();
  void Click();
  void Init();

private:
  std::vector<std::pair<State, std::shared_ptr<Button>>> ButtonVec;
};

