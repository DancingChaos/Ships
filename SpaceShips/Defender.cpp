#include "Defender.h"
#include "GameSettings.h"


Defender::Defender()
{
  this->Type = ShipType::DefenderType;
  this->HP = 250.f;
  this->Shield = 250.f;
  this->Bounty = 500;
  this->Fuel = 100.f;
  this->Speed = 0.3f;
  this->RotationSpeed = 2.0f;

  this->IsMoving = false;

  FileName = TypeToString(Type);

  if (ShipTexture.loadFromFile(PathToImage + FileName + FileExt))
    ShipSprite.setTexture(ShipTexture);

  int PositionIndex = 0;

  if (IsPlayer)
  {
    if (GameSettings::IsEven(GameSettings::PlayerDefenderCount))
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 + GameSettings::PlayerDefenderCount + 1) * GraphSystem::MAP_GRID_WIDTH + 7;
    else
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 - GameSettings::PlayerDefenderCount) * GraphSystem::MAP_GRID_WIDTH + 7;
    ShipSprite.setRotation(90.f);
  }
  else
  {
    if (GameSettings::IsEven(GameSettings::BotDefenderCount))
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 + GameSettings::BotDefenderCount + 1) * GraphSystem::MAP_GRID_WIDTH + GraphSystem::MAP_GRID_WIDTH - 8;
    else
      PositionIndex = (GraphSystem::MAP_GRID_HEIGHT / 2 - GameSettings::BotDefenderCount) * GraphSystem::MAP_GRID_WIDTH + GraphSystem::MAP_GRID_WIDTH - 8;
    GameSettings::BotDefenderCount++;

    ShipSprite.setRotation(270.f);
  }

  Position = GraphSystem::GetNodes()[PositionIndex];

  if (Position)
    ShipSprite.setPosition(Position->NodeRect.getPosition().x + Position->NodeRect.getSize().x / 2, Position->NodeRect.getPosition().y + Position->NodeRect.getSize().y / 2);

  ShipSprite.setOrigin(float(ShipTexture.getSize().x / 2), float(ShipTexture.getSize().y / 2));
}

void Defender::Behavior()
{

}

void Defender::Action()
{

}
