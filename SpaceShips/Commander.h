#pragma once
#include "Ship.h"

class Commander : public Ship
{
public:
  Commander();

  virtual void Behavior() override;
  virtual void Action() override;

private:
  
};

