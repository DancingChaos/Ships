#pragma once
#include <SFML/Graphics.hpp>
#include "GraphSystem.h"
#include "GameSettings.h"

enum ShipType
{
  None,
  CommanderType,
  AttackerType,
  DefenderType,
  SupportType,
  CaravanType
};

class Ship
{
public:
  Ship();
  virtual void Update();
  virtual void Draw();

  void SetTargetPosition();
  void PassTheSell(Direction Dir);
  void GoingToTarget();
  void SetRotationBorders(float Left, float Right);
  void SetShipForAttack();
  void ChooseRandomShipForAttack();
  void TakeDamage(float Damage);

  virtual void Behavior();
  virtual void Action();

  float GetHP();
  Ship* GetShipForAttack();
  ShipType GetShipType();
  sf::Sprite& GetSprite();
  std::shared_ptr<Node> & GetPositionNode();

  bool IsAlive();
  bool IsRotatedToMove();
  bool IsRotatedToStay();
  bool IsShipMoving();

protected:
  float HP{};
  float Fuel{};
  float FuelConsumption{};
  float Speed{};
  float RotationSpeed{};

  float LocalDistanceTraveled{};
  float RotationAngleBorderRight{};
  float RotationAngleBorderLeft{};
  float DefaultRotationAngleBorderRight{};
  float DefaultRotationAngleBorderLeft{};

  int Ammo{};
  int Bounty{};

  bool IsMoving{};
  bool IsDoingAction{};
  bool IsPlayer{};

  std::string FileName;

  const std::string TypeToString(ShipType Type);
  const std::string PathToImage = "..\\Images\\";
  const std::string FileExt = ".png";

  sf::Vector2f ViewDirection{};

  std::shared_ptr<Node> Position;
  std::shared_ptr<Node> TargetPosition;
  std::vector<std::pair<std::shared_ptr<Node>, Direction>> Path;

  Ship* ShipForAttack;
  ShipType Type;

  sf::RectangleShape tmp;

  sf::Texture ShipTexture;
  sf::Sprite ShipSprite;
};