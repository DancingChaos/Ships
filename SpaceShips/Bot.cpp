#include "Bot.h"
#include <thread>

#include "Attacker.h"
#include "Caravan.h"
#include "Defender.h"
#include "Commander.h"
#include "Support.h"

void Bot::Init()
{
  ShipVec.push_back(new Commander());
  RandomFleet();
}

void Bot::DrawFleet()
{
  for (auto& it : ShipVec)
    it->Draw();
}