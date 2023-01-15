#include "User.h"
#include <thread>
#include "GameManager.h"
#include "Attacker.h"
#include "Defender.h"
#include "Caravan.h"
#include "Commander.h"
#include "Support.h"
void User::DrawFleet()
{
  for (auto& it : ShipVec)
    it->Draw();
}

void User::RandomFleet()
{
  srand(time(0));
  int AttackerCount = rand() % GameSettings::ATTACKERS_LIMIT + 1;
  int DefenderCount = rand() % GameSettings::DEFENDER_LIMIT + 1;
  int SupportCount = rand() % GameSettings::SUPPORT_LIMIT + 1;
  int CaravanCount = rand() % GameSettings::CARAVAN_LIMIT + 1;

  ShipVec.push_back(new Defender());

  for (size_t Count = 0; Count < AttackerCount; Count++)
    ShipVec.push_back(new Attacker());

  for (size_t Count = 0; Count < DefenderCount; Count++)
    ShipVec.push_back(new Defender());

  for (size_t Count = 0; Count < SupportCount; Count++)
    ShipVec.push_back(new Support());

  for (size_t Count = 0; Count < CaravanCount; Count++)
    ShipVec.push_back(new Caravan());
}

void User::Update()
{
  for (auto it = ShipVec.begin(); it != ShipVec.end(); it++)
  {
    if (!(*it)->IsAlive())
    {
      ShipVec.erase(it);
      break;
    }
    else
    {
      /*std::thread(&Ship::Update, (*it)).detach();*/
      (*it)->Update();
    }
  }
}

std::vector <Ship*>& User::GetFleet()
{
  return ShipVec;
}
