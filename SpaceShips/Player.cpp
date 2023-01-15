#include "Player.h"
#include "GameSettings.h"
#include <thread>
#include "GameManager.h"


void Player::SelectShip()
{
  for (auto& it : ShipVec)
    if (it->GetSprite().getGlobalBounds().contains(GameSettings::GetMousePos().x, GameSettings::GetMousePos().y))
      SelectedShip = it;
}

void Player::MoveShip()
{
  if (SelectedShip && !SelectedShip->IsShipMoving())
    SelectedShip->SetTargetPosition();
}

void Player::SetEnemyShip()
{
  if (SelectedShip && SelectedShip->GetShipType() == AttackerType)
    SelectedShip->SetShipForAttack();
}

bool Player::IsShipInFleet(ShipType Type)
{
  if (GameSettings::PlayerCommanderCount > 0 && Type == CommanderType)
    return true;
  if (GameSettings::PlayerAttackersCount > 0 && Type == AttackerType)
    return true;
  if (GameSettings::PlayerDefenderCount > 0 && Type == DefenderType)
    return true;
  if (GameSettings::PlayerSupportCount > 0 && Type == SupportType)
    return true;
  if (GameSettings::PlayerCaravanCount > 0 && Type == CaravanType)
    return true;

  return false;
}

bool Player::IsShipOverlimited(ShipType Type)
{
  if (GameSettings::PlayerCommanderCount >= GameSettings::COMMANDER_LIMIT && Type == CommanderType)
    return true;
  if (GameSettings::PlayerAttackersCount >= GameSettings::ATTACKERS_LIMIT && Type == AttackerType)
    return true;
  if (GameSettings::PlayerDefenderCount >= GameSettings::DEFENDER_LIMIT && Type == DefenderType)
    return true;
  if (GameSettings::PlayerSupportCount >= GameSettings::SUPPORT_LIMIT && Type == SupportType)
    return true;
  if (GameSettings::PlayerCaravanCount >= GameSettings::CARAVAN_LIMIT && Type == CaravanType)
    return true;

  return false;
}

void Player::BuyShip(std::pair<Ship*, const int> NewShip)
{
  if (Money - NewShip.second >= 0 && !IsShipOverlimited(NewShip.first->GetShipType()))
  {
    switch (NewShip.first->GetShipType())
    {
    case CommanderType:
      GameSettings::PlayerCommanderCount++;
      break;
    case AttackerType:
      GameSettings::PlayerAttackersCount++;
      break;
    case DefenderType:
      GameSettings::PlayerDefenderCount++;
      break;
    case SupportType:
      GameSettings::PlayerSupportCount++;
      break;
    case CaravanType:
      GameSettings::PlayerCaravanCount++;
      break;
    }
    Money -= NewShip.second;
    ShipVec.push_back(NewShip.first);
  }
}

void Player::SellShip(std::pair<Ship*, const int> ShipToSell)
{
  if (IsShipInFleet(ShipToSell.first->GetShipType()))
  {
    switch (ShipToSell.first->GetShipType())
    {
    case CommanderType:
      GameSettings::PlayerCommanderCount--;
      break;
    case AttackerType:
      GameSettings::PlayerAttackersCount--;
      break;
    case DefenderType:
      GameSettings::PlayerDefenderCount--;
      break;
    case SupportType:
      GameSettings::PlayerSupportCount--;
      break;
    case CaravanType:
      GameSettings::PlayerCaravanCount--;
      break;
    }
    Money += ShipToSell.second;
    for (auto it = ShipVec.begin(); it != ShipVec.end(); it++)
    {
      if ((*it)->GetShipType() == ShipToSell.first->GetShipType())
      {
        ShipVec.erase(it);
        break;
      }
    }
  }
}

int Player::GetMoneyCount()
{
  return Money;
}

