#pragma once
#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"

enum Direction
{
  NorthWest,
  NorthEast,
  SouthWest,
  SouthEast,
  North,
  South,
  East,
  West
};

struct Node
{
  bool Obstacle;
  bool Visited;

  float GlobalGoal;
  float LocalGoal;

  int X;
  int Y;

  sf::RectangleShape NodeRect;

  std::vector<std::shared_ptr<Node>> Neighbors;
  std::shared_ptr<Node> Parent;

  sf::Vector2f Size;
  float Border;

  Node()
  {
    Size = sf::Vector2f(64.f, 64.f);

    bool Obstacle = false;
    bool Visited = false;

    float GlobalGoal = 0.f;
    float LocalGoal = 0.f;
    float Border = 10.f;

    int X = 0;
    int Y = 0;

    Parent = nullptr;

    NodeRect.setFillColor(sf::Color::Cyan);
    NodeRect.setSize(sf::Vector2f(Size.x, Size.y));
    NodeRect.setOutlineColor(sf::Color::Black);
  }
};

class GraphSystem
{
public:

  static void Init();
  static void Draw();
  static void FindPath(std::shared_ptr<Node> ShipPosition);

  static Direction DetermineDirection(std::shared_ptr<Node> First, std::shared_ptr<Node> Second);

  static std::vector<std::pair<std::shared_ptr<Node>, Direction>> CreatePath();
  static std::shared_ptr<Node> GetTargetPosition();
  static std::vector<std::shared_ptr<Node>> & GetNodes();


  static const int MAP_GRID_WIDTH = 25;
  static const int MAP_GRID_HEIGHT = 15;

private:
  static std::vector<std::shared_ptr<Node>> Nodes;

  static std::shared_ptr<Node> NodeStart;
  static std::shared_ptr<Node> NodeEnd;
};

