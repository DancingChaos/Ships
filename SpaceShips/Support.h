#include "Ship.h"


class Support : public Ship
{
public:
  Support();

  virtual void Behavior() override;
  virtual void Action() override;


private:
  float FuelSupply;
};

