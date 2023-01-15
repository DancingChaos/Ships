#pragma once
#include "Ship.h"

class User
{
public:
  void DrawFleet();
  void Update();
  void RandomFleet();

  virtual std::vector <Ship*>& GetFleet();

protected:

  Ship* SelectedShip;
  std::vector <Ship*> ShipVec;
};

