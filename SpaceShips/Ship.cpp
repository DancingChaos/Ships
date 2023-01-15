#include "Ship.h"
#include "GameSettings.h"
#include "GameManager.h"

Ship::Ship()
{
  IsPlayer = true;

  FileName = TypeToString(Type);

  if (ShipTexture.loadFromFile(PathToImage + "PlayerAttacker" + FileExt))
    ShipSprite.setTexture(ShipTexture);

  this->Type = Type;

  this->HP = 0;
  this->Bounty = 0;
  this->Fuel = 0;
  this->Speed = 0;
  this->Ammo = 0;
  this->RotationSpeed = 0;

  this->IsMoving = false;
  this->IsDoingAction = false;

  if (IsPlayer)
  {
    this->DefaultRotationAngleBorderLeft = 89.f;
    this->DefaultRotationAngleBorderRight = 91.f;
  }
  else
  {
    this->DefaultRotationAngleBorderLeft = 269.f;
    this->DefaultRotationAngleBorderRight = 271.f;
  }


  this->RotationAngleBorderLeft = DefaultRotationAngleBorderLeft;
  this->RotationAngleBorderRight = DefaultRotationAngleBorderRight;

  this->LocalDistanceTraveled = 0;
}

void Ship::Update()
{
  if (ShipForAttack && !ShipForAttack->IsAlive())
    ShipForAttack = nullptr;

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

void Ship::Draw()
{
  GameSettings::GetWindow().draw(ShipSprite);
  
}

const std::string Ship::TypeToString(ShipType Type)
{
  std::string Prefix;
  if (GameSettings::GetState() == MainMenu || GameSettings::GetState() == Shoping)
  {
    IsPlayer = true;
    Prefix = "Player";
  }
  if (GameSettings::GetState() == Playing)
  {
    IsPlayer = false;
    Prefix = "Bot";
  }

  if (Type == ShipType::AttackerType)
    return Prefix + "Attacker";
  if (Type == ShipType::CaravanType)
    return Prefix + "Caravan";
  if (Type == ShipType::CommanderType)
    return Prefix + "Commander";
  if (Type == ShipType::DefenderType)
    return Prefix + "Defender";
  if (Type == ShipType::SupportType)
    return Prefix + "Support";

  return "";
}

bool Ship::IsRotatedToStay()
{
  if (!(ShipSprite.getRotation() <= DefaultRotationAngleBorderRight && ShipSprite.getRotation() >= DefaultRotationAngleBorderLeft))
    return false;

  return true;
}

bool Ship::IsRotatedToMove()
{
  if (!(ShipSprite.getRotation() <= RotationAngleBorderRight && ShipSprite.getRotation() >= RotationAngleBorderLeft))
  {
    if (ShipSprite.getRotation() > RotationAngleBorderRight)
      ShipSprite.rotate(-RotationSpeed);

    if (ShipSprite.getRotation() < RotationAngleBorderLeft)
      ShipSprite.rotate(RotationSpeed);

    return false;
  }

  return true;
}

void Ship::SetShipForAttack()
{
  for (auto& it : GameManager::GetGame()->GetBot()->GetFleet())
    if (it->GetSprite().getGlobalBounds().contains(GameSettings::GetMousePos().x, GameSettings::GetMousePos().y))
      ShipForAttack = it;
}

void Ship::ChooseRandomShipForAttack()
{
  if (GameManager::GetGame()->GetPlayer()->GetFleet().empty())
    return;
  int Rand = rand() % GameManager::GetGame()->GetPlayer()->GetFleet().size() + 1;
  int i = 0;
  for (auto& it : GameManager::GetGame()->GetPlayer()->GetFleet())
  {
    if (Rand == i)
    {
      ShipForAttack = it;
    }
    i++;
  }
}

Ship* Ship::GetShipForAttack()
{
  return ShipForAttack;
}

void Ship::Action()
{

}

void Ship::Behavior()
{

}


void Ship::GoingToTarget()
{
  if (!Path.empty())
  {
    IsMoving = IsRotatedToMove();

    if (!IsMoving)
      return;

    Position->Obstacle = false;

    if (LocalDistanceTraveled >= Position->Size.x)
    {
      LocalDistanceTraveled = 0;
      Fuel -= FuelConsumption;
      Position = Path.front().first;
      Path.erase(Path.begin());
    }

    if (!Path.empty())
      PassTheSell(Path.front().second);
    else
    {
      IsMoving = false;
      TargetPosition = nullptr;
      Position->Obstacle = true;
    }
  }
}

void Ship::PassTheSell(Direction Dir)
{
  switch (Dir)
  {
  case NorthWest:
    LocalDistanceTraveled += Speed;
    ShipSprite.move(-Speed, -Speed);
    SetRotationBorders(324.f, 326.f);
    break;
  case NorthEast:
    LocalDistanceTraveled += Speed;
    ShipSprite.move(Speed, -Speed);
    SetRotationBorders(44.f, 46.f);
    break;
  case SouthWest:
    LocalDistanceTraveled += Speed;
    ShipSprite.move(-Speed, Speed);
    SetRotationBorders(224.f, 226.f);
    break;
  case SouthEast:
    LocalDistanceTraveled += Speed;
    ShipSprite.move(Speed, Speed);
    SetRotationBorders(134.f, 136.f);
    break;
  case North:
    LocalDistanceTraveled += Speed;
    ShipSprite.move(0, -Speed);
    SetRotationBorders(0.f, 2.f);
    break;
  case South:
    LocalDistanceTraveled += Speed;
    ShipSprite.move(0, Speed);
    SetRotationBorders(180.f, 182.f);
    break;
  case East:
    LocalDistanceTraveled += Speed;
    ShipSprite.move(Speed, 0);
    SetRotationBorders(89.f, 91.f);
    break;
  case West:
    LocalDistanceTraveled += Speed;
    ShipSprite.move(-Speed, 0);
    SetRotationBorders(269.f, 271.f);
    break;
  }
}

void Ship::TakeDamage(float Damage)
{
  HP -= Damage;
}

sf::Sprite& Ship::GetSprite()
{
  return ShipSprite;
}

float Ship::GetHP()
{
  return HP;
}

bool Ship::IsAlive()
{
  if (HP > 0)
    return true;
  Position->Obstacle=false;
  return false;
}

ShipType Ship::GetShipType()
{
  return Type;
}

std::shared_ptr<Node>& Ship::GetPositionNode()
{
  return Position;
}

void Ship::SetRotationBorders(float Left, float Right)
{
  RotationAngleBorderLeft = Left;
  RotationAngleBorderRight = Right;
}

void Ship::SetTargetPosition()
{
  if (GraphSystem::GetTargetPosition() != nullptr)
  {
    TargetPosition = GraphSystem::GetTargetPosition();
    GraphSystem::FindPath(Position);
    Path = GraphSystem::CreatePath();
  }
}

bool Ship::IsShipMoving()
{
  return IsMoving;
}

