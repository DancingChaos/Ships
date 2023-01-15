#pragma once
#include "Ship.h"
#include "GameManager.h"

struct Projectile
{
  float Speed;
  float Damage;

  bool IsAlive;
  bool IsPlayersProj;

  sf::Vector2f Position;
  sf::Vector2f Direction;

  sf::Texture ProjectileTexture;
  sf::Sprite  ProjectileSprite;

  Projectile(sf::Vector2f Direction, sf::Vector2f Position, bool IsPlayer)
  {
    if (ProjectileTexture.loadFromFile("..\\Images\\Projectile.png"))
      ProjectileSprite.setTexture(ProjectileTexture);

    this->Direction = Direction;
    this->ProjectileSprite.setScale(3.f, 3.f);
    this->ProjectileSprite.setPosition(Position);
    
    this->IsAlive = true;
    this->IsPlayersProj = IsPlayer;

    this->Speed = 3.f;
    this->Damage = 20;
  }

  void Collision()
  {
    for (auto it = GameManager::GetGame()->GetBot()->GetFleet().begin(); it != GameManager::GetGame()->GetBot()->GetFleet().end(); it++)
    {
      if(IsPlayersProj)
      if (ProjectileSprite.getGlobalBounds().intersects((*it)->GetSprite().getGlobalBounds()))
      {
        if (!(*it)->IsAlive())
        {
          if ((*it))
            delete (*it);

          GameManager::GetGame()->GetBot()->GetFleet().erase(it);
          break;
        }
        else
        {
          (*it)->TakeDamage(Damage);
          IsAlive = false;
        }
      }
    }
  }
  void PlayerCollision()
  {
    for (auto it = GameManager::GetGame()->GetPlayer()->GetFleet().begin(); it != GameManager::GetGame()->GetPlayer()->GetFleet().end(); it++)
    {
        if (ProjectileSprite.getGlobalBounds().intersects((*it)->GetSprite().getGlobalBounds()))
        {
          if (!(*it)->IsAlive())
          {
            if ((*it))
              delete (*it);

            GameManager::GetGame()->GetPlayer()->GetFleet().erase(it);
            break;
          }
          else
          {
            (*it)->TakeDamage(Damage);
            IsAlive = false;
          }
        }
    }
  }
};



class Attacker : public Ship
{
public:
  Attacker();
  void Shoot();

  virtual void Behavior() override;
  virtual void Action() override;
  virtual void Draw() override;
  virtual void Update() override;
  void ClearProjectiles();

  sf::Vector2f GetProjectileDirection();
  std::vector<std::shared_ptr<Projectile>> GetProjVec();


private:
  sf::Clock ReadyToShoot;
  const float ATTACK_DELAY = 1.f;
  std::vector<std::shared_ptr<Projectile>> ProjectileVec;
};

