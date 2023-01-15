#pragma once
#include <vector>
#include "Projectile.h"
class ProjectileManager
{
public:
  void Update();
  void Draw();
  void CheckCollision();
  void Spawn(sf::Vector2f FlyDirection);

private:

  std::vector<std::shared_ptr<Projectile>> ProjectilesVec;
};

