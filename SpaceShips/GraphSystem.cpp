#include "GraphSystem.h"
#include "GameSettings.h"
#include <list>

std::vector<std::shared_ptr<Node>> GraphSystem::Nodes;

std::shared_ptr<Node> GraphSystem::NodeStart;
std::shared_ptr<Node> GraphSystem::NodeEnd;

void GraphSystem::Init()
{
  Nodes.reserve(MAP_GRID_WIDTH * MAP_GRID_HEIGHT);

  for (int X = 0; X < MAP_GRID_WIDTH; X++)
    for (int Y = 0; Y < MAP_GRID_HEIGHT; Y++)
      Nodes.emplace_back(std::make_shared<Node>());

  for (int X = 0; X < MAP_GRID_WIDTH; X++)
  {
    for (int Y = 0; Y < MAP_GRID_HEIGHT; Y++)
    {
      int NodeIdx = Y * MAP_GRID_WIDTH + X;

      Nodes[NodeIdx]->X = X;
      Nodes[NodeIdx]->Y = Y;
      Nodes[NodeIdx]->Obstacle = false;
      Nodes[NodeIdx]->Parent = nullptr;
      Nodes[NodeIdx]->Visited = false;
      Nodes[NodeIdx]->Size = sf::Vector2f(64.f, 64.f);

      Nodes[NodeIdx]->NodeRect.setOutlineThickness(0.5f);
      Nodes[NodeIdx]->NodeRect.setOutlineColor(sf::Color(0,0,0,100));
      Nodes[NodeIdx]->NodeRect.setPosition(X * Nodes[NodeIdx]->Size.x, Y * Nodes[NodeIdx]->Size.y);
    }
  }

  for (int X = 0; X < MAP_GRID_WIDTH; X++)
  {
    for (int Y = 0; Y < MAP_GRID_HEIGHT; Y++)
    {
      int NodeIdx = Y * MAP_GRID_WIDTH + X;

      if (Y > 0)
        Nodes[NodeIdx]->Neighbors.emplace_back(std::shared_ptr(Nodes[(Y - 1) * MAP_GRID_WIDTH + X]));
      if (Y < MAP_GRID_HEIGHT - 1)
        Nodes[NodeIdx]->Neighbors.emplace_back(std::shared_ptr(Nodes[(Y + 1) * MAP_GRID_WIDTH + X]));
      if (X > 0)
        Nodes[NodeIdx]->Neighbors.emplace_back(std::shared_ptr(Nodes[Y * MAP_GRID_WIDTH + (X - 1)]));
      if (X < MAP_GRID_WIDTH - 1)
        Nodes[NodeIdx]->Neighbors.emplace_back(std::shared_ptr(Nodes[Y * MAP_GRID_WIDTH + (X + 1)]));
      if (Y > 0 && X > 0)
        Nodes[NodeIdx]->Neighbors.emplace_back(std::shared_ptr(Nodes[(Y - 1) * MAP_GRID_WIDTH + (X - 1)]));
      if (Y < MAP_GRID_HEIGHT - 1 && X < MAP_GRID_WIDTH - 1)
        Nodes[NodeIdx]->Neighbors.emplace_back(std::shared_ptr(Nodes[(Y + 1) * MAP_GRID_WIDTH + (X + 1)]));
      if (X > 0 && Y < MAP_GRID_HEIGHT - 1)
        Nodes[NodeIdx]->Neighbors.emplace_back(std::shared_ptr(Nodes[(Y + 1) * MAP_GRID_WIDTH + (X - 1)]));
      if (Y > 0 && X < MAP_GRID_WIDTH - 1)
        Nodes[NodeIdx]->Neighbors.emplace_back(std::shared_ptr(Nodes[(Y - 1) * MAP_GRID_WIDTH + (X + 1)]));
    }
  }
}

void GraphSystem::Draw()
{
  for (int X = 0; X < MAP_GRID_WIDTH; X++)
    for (int Y = 0; Y < MAP_GRID_HEIGHT; Y++)
    {
      auto NodeIdx = Y * MAP_GRID_WIDTH + X;

      Nodes[NodeIdx]->NodeRect.setFillColor(sf::Color::Transparent);

      if (NodeEnd == Nodes[NodeIdx])
        Nodes[NodeIdx]->NodeRect.setFillColor(sf::Color(51, 0, 102, 30));

      if (Nodes[NodeIdx]->Obstacle)
        Nodes[NodeIdx]->NodeRect.setFillColor(sf::Color(100, 100, 100));

      GameSettings::GetWindow().draw(Nodes[NodeIdx]->NodeRect);
    }

  if (NodeEnd != nullptr)
  {
    std::shared_ptr<Node> Tmp = NodeEnd;
    while (Tmp->Parent != nullptr)
    {
      sf::VertexArray lines(sf::LinesStrip, 2);
      lines[0].color = sf::Color::Magenta;
      lines[1].color = sf::Color::Magenta;
      lines[0].position = sf::Vector2f(Tmp->X * Tmp->Size.x + Tmp->Size.x / 2, Tmp->Y * Tmp->Size.y + Tmp->Size.y / 2);
      lines[1].position = sf::Vector2f(Tmp->Parent->X * Tmp->Parent->Size.x + Tmp->Parent->Size.x / 2, Tmp->Parent->Y * Tmp->Parent->Size.y + Tmp->Parent->Size.y / 2);

      GameSettings::GetWindow().draw(lines);

      Tmp = Tmp->Parent;
    }
  }
}

std::vector<std::pair<std::shared_ptr<Node>, Direction>> GraphSystem::CreatePath()
{
  std::vector<std::pair<std::shared_ptr<Node>, Direction>> Path;
  if (NodeEnd != nullptr)
  {
    std::shared_ptr<Node> Tmp = NodeEnd;
    while (Tmp->Parent != nullptr)
    {
      Path.insert(Path.begin(), std::pair<std::shared_ptr<Node>, Direction> (Tmp, DetermineDirection(Tmp->Parent, Tmp)));
      Tmp = Tmp->Parent;
    }
  }

  return Path;
}

Direction GraphSystem::DetermineDirection(std::shared_ptr<Node> First, std::shared_ptr<Node> Second)
{
  auto ResultX = First->X - Second->X;
  auto ResultY = First->Y - Second->Y;

  if (ResultX == 1 && ResultY == 1)
    return NorthWest;
  if (ResultX == -1  && ResultY == -1)
    return SouthEast;
  if (ResultX == 1 && ResultY == -1)
    return SouthWest;
  if (ResultX == -1 && ResultY == 1)
    return NorthEast;
  if (ResultY == -1)
    return South;
  if (ResultY == 1)
    return North;
  if (ResultX == -1)
    return East;
  if (ResultX == 1)
    return West;

  return North;
}

void GraphSystem::FindPath(std::shared_ptr<Node> ShipPosition)
{
  NodeStart = ShipPosition;
  NodeEnd = GetTargetPosition();

  if (!NodeStart && !NodeEnd)
    return;

  for (int X = 0; X < MAP_GRID_WIDTH; X++)
  {
    for (int Y = 0; Y < MAP_GRID_HEIGHT; Y++)
    {
      int NodeIdx = Y * MAP_GRID_WIDTH + X;

      Nodes[NodeIdx]->Visited = false;
      Nodes[NodeIdx]->GlobalGoal = INFINITY;
      Nodes[NodeIdx]->LocalGoal = INFINITY;
      Nodes[NodeIdx]->Parent = nullptr;
    }
  }

  auto Distance = [](std::shared_ptr<Node> A, std::shared_ptr<Node> B)
  {
    return sqrtf(float((A->X - B->X) * (A->X - B->X)) + float((A->Y - B->Y) * (A->Y - B->Y)));
  };

  auto Heuristic = [Distance](std::shared_ptr<Node> A, std::shared_ptr<Node> B)
  {
    return Distance(A, B);
  };

  std::shared_ptr<Node> NodeCurrent = NodeStart;
  NodeStart->LocalGoal = 0.0f;
  NodeStart->GlobalGoal = Heuristic(NodeStart, NodeEnd);

  std::list<std::shared_ptr<Node>> NotTestedNodes;
  NotTestedNodes.push_back(NodeStart);
  while (!NotTestedNodes.empty())
  {
    NotTestedNodes.sort([](const std::shared_ptr<Node> A, const std::shared_ptr<Node> B) {
      return A->GlobalGoal < B->GlobalGoal;
      });

    while (!NotTestedNodes.empty() && NotTestedNodes.front()->Visited)
      NotTestedNodes.pop_front();

    if (NotTestedNodes.empty())
      break;

    NodeCurrent = NotTestedNodes.front();
    NodeCurrent->Visited = true;

    std::shared_ptr<Node> ClosestNeighbor = nullptr;

    for (auto Neighbor : NodeCurrent->Neighbors)
    {
      if (!Neighbor->Visited && !Neighbor->Obstacle)
        NotTestedNodes.push_back(Neighbor);

      float PossiblyLowerGoal = NodeCurrent->LocalGoal + Distance(NodeCurrent, Neighbor);

      if (PossiblyLowerGoal < Neighbor->LocalGoal)
      {
        Neighbor->Parent = NodeCurrent;
        Neighbor->LocalGoal = PossiblyLowerGoal;
        Neighbor->GlobalGoal = Neighbor->LocalGoal + Heuristic(Neighbor, NodeEnd);
      }
    }
  }
}

std::shared_ptr<Node> GraphSystem::GetTargetPosition()
{
  for (auto& Node : Nodes)
    if (Node->NodeRect.getGlobalBounds().contains(GameSettings::GetMousePos().x, GameSettings::GetMousePos().y) && !Node->Obstacle)
      return Node;

  return nullptr;
}

std::vector<std::shared_ptr<Node>> & GraphSystem::GetNodes()
{
  return Nodes;
}
