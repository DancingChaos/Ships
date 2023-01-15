#include "GameManager.h"
#include <iostream>
#include <memory>

std::unique_ptr<Game> GameManager::GamePtr = std::make_unique<Game>();

std::unique_ptr<Game> & GameManager::GetGame()
{
  return GamePtr;
}
