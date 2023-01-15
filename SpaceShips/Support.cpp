#include "Support.h"

Support::Support()
{
  this->Type = ShipType::SupportType;
  this->HP = 50.f;
  this->Bounty = 200;
  this->Fuel = 100.f;
  this->Speed = 0.4f;
  this->RotationSpeed = 2.0f;

  this->IsMoving = false;

  FileName = TypeToString(Type);

  if (ShipTexture.loadFromFile(PathToImage + FileName + FileExt))
    ShipSprite.setTexture(ShipTexture);

  int PositionIndex = 0;

  if (IsPlayer)
  {
    if (GameSettings::IsEven(GameSettings::PlayerSupportCount))
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 + GameSettings::PlayerSupportCount + 1) * GraphSystem::MAP_GRID_WIDTH + 2;
    else
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 - GameSettings::PlayerSupportCount) * GraphSystem::MAP_GRID_WIDTH + 2;
    ShipSprite.setRotation(90.f);
  }
  else
  {
    if (GameSettings::IsEven(GameSettings::BotSupportCount))
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 + GameSettings::BotSupportCount + 1) * GraphSystem::MAP_GRID_WIDTH + GraphSystem::MAP_GRID_WIDTH - 3;
    else
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 - GameSettings::BotSupportCount) * GraphSystem::MAP_GRID_WIDTH + GraphSystem::MAP_GRID_WIDTH - 3;
    GameSettings::BotSupportCount++;
    ShipSprite.setRotation(270.f);
  }

  Position = GraphSystem::GetNodes()[PositionIndex];

  if (Position)
    ShipSprite.setPosition(Position->NodeRect.getPosition().x + Position->NodeRect.getSize().x / 2, Position->NodeRect.getPosition().y + Position->NodeRect.getSize().y / 2);

  ShipSprite.setRotation(90.f);
  ShipSprite.setOrigin(float(ShipTexture.getSize().x / 2), float(ShipTexture.getSize().y / 2));
}

void Support::Behavior()
{

}

void Support::Action()
{

}

