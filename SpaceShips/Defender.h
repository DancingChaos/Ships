#pragma once
#include "Ship.h"

class Defender : public Ship
{
public:
  Defender();

  virtual void Behavior() override;
  virtual void Action() override;


private:
  float Shield;
};

