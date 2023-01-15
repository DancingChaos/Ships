#include "Projectile.h"
#include "GameSettings.h"

Projectile::Projectile(sf::Vector2f Position)
{
  if (ProjectileTexture.loadFromFile("..\\Images\\Projectile.png"))
    ProjectileSprite.setTexture(ProjectileTexture);

  ProjectileSprite.setPosition(Position);
}

void Projectile::Update()
{
  Fly();
}

void Projectile::Draw()
{
  GameSettings::GetWindow().draw(ProjectileSprite);
}

void Projectile::Fly()
{
  ProjectileSprite.move(Direction.x * Speed, Direction.y * Speed);
}



void Projectile::Hit()
{

}


