#pragma once
#include "User.h"

class Player : public User
{
public:
  Player()
  {
    SelectedShip=nullptr;
    Money = 50000;
  }

  void MoveShip();
  void BuyShip(std::pair<Ship *, const int> NewShip);
  void SellShip(std::pair<Ship *, const int> ShipToSell);
  void SelectShip();
  void SetEnemyShip();

  bool IsShipOverlimited(ShipType Type);
  bool IsShipInFleet(ShipType Type);

  int GetMoneyCount();

private:
  int Money;

  Ship * SelectedShip;

  const int FLEET_LIMIT = 15;
};