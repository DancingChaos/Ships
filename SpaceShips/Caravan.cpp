#include "Caravan.h"


Caravan::Caravan()
{
  this->Type = ShipType::CaravanType;
  this->HP = 25.f;
  this->Bounty = 100;
  this->Fuel = 100.f;
  this->Speed = 0.2f;
  this->RotationSpeed = 2.0f;

  this->IsMoving = false;

  FileName = TypeToString(Type);

  if (ShipTexture.loadFromFile(PathToImage + FileName + FileExt))
    ShipSprite.setTexture(ShipTexture);

  int PositionIndex = 0;


  if (IsPlayer)
  {
    if (GameSettings::IsEven(GameSettings::PlayerCaravanCount))
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 + GameSettings::PlayerCaravanCount + 1) * GraphSystem::MAP_GRID_WIDTH;
    else
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 - GameSettings::PlayerCaravanCount) * GraphSystem::MAP_GRID_WIDTH;
    ShipSprite.setRotation(90.f);
  }
  else
  {
    if (GameSettings::IsEven(GameSettings::BotCaravanCount))
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 + GameSettings::BotCaravanCount + 1) * GraphSystem::MAP_GRID_WIDTH + GraphSystem::MAP_GRID_WIDTH - 1;
    else
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 - GameSettings::BotCaravanCount) * GraphSystem::MAP_GRID_WIDTH + GraphSystem::MAP_GRID_WIDTH - 1;
    ShipSprite.setRotation(270.f);
    GameSettings::BotCaravanCount++;
  }

  Position = GraphSystem::GetNodes()[PositionIndex];

  if (Position)
    ShipSprite.setPosition(Position->NodeRect.getPosition().x + Position->NodeRect.getSize().x / 2, Position->NodeRect.getPosition().y + Position->NodeRect.getSize().y / 2);

  ShipSprite.setRotation(90.f);
  ShipSprite.setOrigin(float(ShipTexture.getSize().x / 2), float(ShipTexture.getSize().y / 2));
}

void Caravan::Behavior()
{

}

void Caravan::Action()
{

}