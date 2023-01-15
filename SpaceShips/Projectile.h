#pragma once
#include <SFML/Graphics.hpp>

class Projectile
{
public:
  Projectile(sf::Vector2f Position);
  void Update();
  void Draw();
  void Fly();
  void Hit();
  void Behavior();
  void Spawn(sf::Vector2f FlyDirection);

private:

  float Speed;
  float Damage;
  sf::Vector2f Position;
  sf::Vector2f Direction;

  sf::Texture ProjectileTexture;
  sf::Sprite  ProjectileSprite;
};

