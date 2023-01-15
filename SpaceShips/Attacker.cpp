#include "Attacker.h"
#include "GameSettings.h"

Attacker::Attacker()
{
  this->Type = ShipType::AttackerType;
  this->HP = 100.f;
  this->Bounty = 500;
  this->Fuel = 100.f;
  this->Speed = 0.75f;
  this->RotationSpeed = 2.0f;
  this->IsMoving = false;
  this->FuelConsumption = 5.f;

  FileName = TypeToString(Type);

  if (ShipTexture.loadFromFile(PathToImage + FileName + FileExt))
    ShipSprite.setTexture(ShipTexture);

  int PositionIndex = 0;

  if (IsPlayer)
  {
    if (GameSettings::IsEven(GameSettings::PlayerAttackersCount))
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 + GameSettings::PlayerAttackersCount) * GraphSystem::MAP_GRID_WIDTH + 4;
    else
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 - GameSettings::PlayerAttackersCount) * GraphSystem::MAP_GRID_WIDTH + 4;
    ShipSprite.setRotation(90.f);
  }
  else
  {
    if (GameSettings::IsEven(GameSettings::BotAttackersCount))
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 + GameSettings::BotAttackersCount + 1) * GraphSystem::MAP_GRID_WIDTH + GraphSystem::MAP_GRID_WIDTH - 5;
    else
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 - GameSettings::BotAttackersCount) * GraphSystem::MAP_GRID_WIDTH + GraphSystem::MAP_GRID_WIDTH - 5;
    ShipSprite.setRotation(270.f);
    GameSettings::BotAttackersCount++;
  }

  Position = GraphSystem::GetNodes()[PositionIndex];

  if (Position)
    ShipSprite.setPosition(Position->NodeRect.getPosition().x + Position->NodeRect.getSize().x / 2, Position->NodeRect.getPosition().y + Position->NodeRect.getSize().y / 2);

  ShipSprite.setOrigin(float(ShipTexture.getSize().x / 2), float(ShipTexture.getSize().y / 2));
}

void Attacker::Behavior()
{
  if (ShipForAttack && !IsMoving)
    IsDoingAction = true;

  if (TargetPosition)
    IsDoingAction = false;

  if (!IsDoingAction)
    return;

  const float PI = 3.14159265;
  if (ShipForAttack && ShipForAttack->IsAlive())
  {
    float dX = ShipForAttack->GetSprite().getPosition().x - ShipSprite.getPosition().x;
    float dY = ShipForAttack->GetSprite().getPosition().y - ShipSprite.getPosition().y;

    float rotation = atan2(dY, dX);
    rotation *= 180 / PI;

    ShipSprite.setRotation(rotation + 90.f);
    Action();
  }
  else
  {
    ShipForAttack = nullptr;
  }
}

void Attacker::ClearProjectiles()
{
  ProjectileVec.clear();
}

void Attacker::Update()
{
  if (!IsPlayer && !ShipForAttack)
    ChooseRandomShipForAttack();

  for (auto it = ProjectileVec.begin(); it != ProjectileVec.end(); it++)
  {
    if ((*it)->IsAlive)
    {
      if ((*it)->IsPlayersProj)
        (*it)->Collision();
      else
        (*it)->PlayerCollision();

      if (ShipForAttack)
        (*it)->Direction = GetProjectileDirection();

      (*it)->ProjectileSprite.move((*it)->Direction.x * Speed, (*it)->Direction.y * Speed);
    }
    else
    {
      ProjectileVec.erase(it);
      break;
    }
  }
  if (GameSettings::GetState() == MainMenu)
    ClearProjectiles();

  if (Fuel <= NULL)
  {
    IsMoving = false;
    TargetPosition = nullptr;
  }

  if (TargetPosition)
    GoingToTarget();

  if (Position)
    Position->Obstacle = true;

  if (!TargetPosition && !IsMoving && !IsRotatedToStay() && !IsDoingAction)
  {
    if (ShipSprite.getRotation() > DefaultRotationAngleBorderRight)
      ShipSprite.rotate(-RotationSpeed);

    if (ShipSprite.getRotation() < DefaultRotationAngleBorderLeft)
      ShipSprite.rotate(RotationSpeed);
  }
  Behavior();
}

std::vector<std::shared_ptr<Projectile>> Attacker::GetProjVec()
{
  return ProjectileVec;
}

sf::Vector2f Attacker::GetProjectileDirection()
{
  sf::Vector2f Dir;
  Dir.x = ShipForAttack->GetSprite().getPosition().x - this->ShipSprite.getPosition().x;
  Dir.y = ShipForAttack->GetSprite().getPosition().y - this->ShipSprite.getPosition().y;

  auto hyp = sqrt(Dir.x * Dir.x + Dir.y * Dir.y);
  Dir.x /= hyp;
  Dir.y /= hyp;

  return Dir;
}

void Attacker::Draw()
{
  GameSettings::GetWindow().draw(ShipSprite);

  for (auto& it : ProjectileVec)
    GameSettings::GetWindow().draw(it->ProjectileSprite);
}

void Attacker::Action()
{
  if (ReadyToShoot.getElapsedTime().asSeconds() > ATTACK_DELAY)
    Shoot();
}

void Attacker::Shoot()
{
  ProjectileVec.push_back(std::make_shared<Projectile>(GetProjectileDirection(), ShipSprite.getPosition(), IsPlayer));

  ReadyToShoot.restart();
}



