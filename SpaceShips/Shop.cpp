#include "Shop.h"

#include "Commander.h"
#include "Attacker.h"
#include "Defender.h"
#include "Support.h"
#include "Caravan.h"
#include "GameManager.h"

void Shop::ReInit()
{
  Clear();
  Init();
}

void Shop::Clear()
{

  for (auto& it : ShipStock)
  {
    if (it.first)
    {
      it.first->GetPositionNode()->Obstacle = false;
      delete it.first;
    }
    if (it.second)
      delete it.second;
  }

  ShipStock.clear();

  for (auto& it : ShopButtonVec)
    if (it.second)
      it.second.reset();

  ShopButtonVec.clear();
}

void Shop::Init()
{
  ShopButtonVec.push_back(std::make_pair(State::Shoping, std::make_shared <Button>(ButtonType::BuyButton)));
  ShopButtonVec.push_back(std::make_pair(State::Shoping, std::make_shared <Button>(ButtonType::SellButton)));
  ShopButtonVec.push_back(std::make_pair(State::Shoping, std::make_shared <Button>(ButtonType::BackButton)));

  ShipStock = {
    std::make_pair < Ship*, sf::Text* >(new Commander(), new sf::Text("1", Aerial, 50)),
    std::make_pair < Ship*, sf::Text* >(new Attacker(),  new sf::Text("2", Aerial, 50)),
    std::make_pair < Ship*, sf::Text* >(new Defender(),  new sf::Text("3", Aerial, 50)),
    std::make_pair < Ship*, sf::Text* >(new Support(),   new sf::Text("4", Aerial, 50)),
    std::make_pair < Ship*, sf::Text* >(new Caravan(),   new sf::Text("5", Aerial, 50)),
  };

  ShipToAction = None;

  int i = 1;
  for (auto It : ShipStock)
  {
    It.first->GetSprite().setScale(2.f, 2.f);
    It.first->GetSprite().setPosition(200.f * i, 500);
    It.second->setPosition(It.first->GetSprite().getPosition().x - 50.f, 600);
    i++;
  }
 
  i = 1;
  for (auto& it : ShopButtonVec)
  {
    if (it.second->GetButtonType() == BackButton)
    {
      it.second->GetSprite().setPosition(50.f, 50.f);
      it.second->GetSprite().setScale(5.f, 5.f);
      continue;
    }

    it.second->GetSprite().setPosition(1400.f, 300.f * i);
    it.second->GetSprite().setScale(7.f, 7.f);
    i++;
  }

  if (MoneyTexture.loadFromFile("..\\Images\\CosmoCoin.png"))
  {
    MoneySprite.setTexture(MoneyTexture);
    MoneySprite.setPosition(1300.f, -50.f);
    MoneySprite.setScale(4.f, 4.f);

  }

  if (Aerial.loadFromFile("..\\Font\\arial.ttf"))
  {
    MoneyCount.setFont(Aerial);
    MoneyCount.setPosition(1200.f, 50.f);
    MoneyCount.setCharacterSize(50);
  }

  ShipToBuyRect.setFillColor(sf::Color::Transparent);
  ShipToBuyRect.setOutlineThickness(3.f);
  ShipToBuyRect.setOutlineColor(sf::Color(51, 0, 102, 100));
  ShipToBuyRect.setSize(sf::Vector2f(120.f, 120.f));
}

void Shop::Update()
{
  for (auto It : ShipStock)
  {
    if (It.first->GetShipType() == CommanderType)
      It.second->setString(std::to_string(GameSettings::PlayerCommanderCount) + " \\ " + std::to_string(GameSettings::COMMANDER_LIMIT));
    if (It.first->GetShipType() == CaravanType)
      It.second->setString(std::to_string(GameSettings::PlayerCaravanCount) + " \\ " + std::to_string(GameSettings::CARAVAN_LIMIT));
    if (It.first->GetShipType() == SupportType)
      It.second->setString(std::to_string(GameSettings::PlayerSupportCount) + " \\ " + std::to_string(GameSettings::SUPPORT_LIMIT));
    if (It.first->GetShipType() == AttackerType)
      It.second->setString(std::to_string(GameSettings::PlayerAttackersCount) + " \\ " + std::to_string(GameSettings::ATTACKERS_LIMIT));
    if (It.first->GetShipType() == DefenderType)
      It.second->setString(std::to_string(GameSettings::PlayerDefenderCount) + " \\ " + std::to_string(GameSettings::DEFENDER_LIMIT));
  }
}

void Shop::Click()
{
  SelectItem();
  for (auto& it : ShopButtonVec)
  {
    if (it.second->GetSprite().getGlobalBounds().contains(GameSettings::GetMousePos().x, GameSettings::GetMousePos().y))
    {
      switch (it.second->GetButtonType())
      {
      case BuyButton:
      {
        if (ShipToAction != None)
          GameManager::GetGame()->GetPlayer()->BuyShip(CreateShipByType(ShipToAction));
        break;
      }
      case SellButton:
        if (ShipToAction != None)
          GameManager::GetGame()->GetPlayer()->SellShip(CreateShipByType(ShipToAction));
        break;
      case BackButton:
        GameSettings::SetState(State::MainMenu);
        break;
      }
    }
  }

  MoneyCount.setString(std::to_string(GameManager::GetGame()->GetPlayer()->GetMoneyCount()));
}


std::pair<Ship *, const int> Shop::CreateShipByType(ShipType Type)
{
  switch (Type)
  {
  case CommanderType:
    return std::make_pair<Ship*, const int>(new Commander(), 5000);
    break;
  case AttackerType:
    return std::make_pair<Ship*, const int>(new Attacker(), 2500);
    break;
  case DefenderType:
    return std::make_pair<Ship*, const int>(new Defender(), 2500);
    break;
  case SupportType:
    return std::make_pair<Ship*, const int>(new Support(), 1500);
    break;
  case CaravanType:
    return std::make_pair<Ship*, const int>(new Caravan(), 1000);
    break;
  }
  return std::pair<Ship*, const int>();
}

void Shop::SelectItem()
{
  for (auto& it : ShipStock)
  {
    if (it.first->GetSprite().getGlobalBounds().contains(GameSettings::GetMousePos().x, GameSettings::GetMousePos().y))
    {
      ShipToAction = it.first->GetShipType();
      ShipToBuyRect.setPosition(it.first->GetSprite().getPosition().x - ShipToBuyRect.getSize().x / 2, it.first->GetSprite().getPosition().y - ShipToBuyRect.getSize().y / 2);
    }
  }
}

void Shop::Draw()
{
  for (auto& it : ShopButtonVec)
    it.second->Draw();

  GameSettings::GetWindow().draw(MoneySprite);
  GameSettings::GetWindow().draw(MoneyCount);

  for (auto& it : ShipStock)
  {
    it.first->Draw();
    GameSettings::GetWindow().draw((*it.second));
  }

  if(ShipToAction != None)
    GameSettings::GetWindow().draw(ShipToBuyRect);
}