#include "Commander.h"
#include "GameSettings.h"


Commander::Commander()
{
  IsPlayer = true;

  this->Type = ShipType::CommanderType;
  this->HP = 250.f;
  this->Bounty = 5000;
  this->Fuel = 100.f;
  this->Speed = 0.1f;
  this->RotationSpeed = 0.5f;
  this->IsMoving = false;

  FileName = TypeToString(Type);

  if (ShipTexture.loadFromFile(PathToImage + FileName + FileExt))
    ShipSprite.setTexture(ShipTexture);

  if (IsPlayer)
  {
    auto PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2) * GraphSystem::MAP_GRID_WIDTH + 1;
    Position = GraphSystem::GetNodes()[PositionIndex];
    ShipSprite.setRotation(90.0f);
  }
  else
  {
    auto PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2) * GraphSystem::MAP_GRID_WIDTH + GraphSystem::MAP_GRID_WIDTH - 2;
    Position = GraphSystem::GetNodes()[PositionIndex];
    ShipSprite.setRotation(270.f);
  }

  if(Position)
    ShipSprite.setPosition(Position->NodeRect.getPosition().x + Position->NodeRect.getSize().x / 2, Position->NodeRect.getPosition().y + Position->NodeRect.getSize().y / 2);
  
  ShipSprite.setOrigin(float(ShipTexture.getSize().x / 2), float(ShipTexture.getSize().y / 2));
}

void Commander::Behavior()
{

}

void Commander::Action()
{

}

