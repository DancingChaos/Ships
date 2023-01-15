#include "Menu.h"
#include "GameManager.h"

void Menu::Init()
{
  ButtonVec.push_back(std::make_pair(State::MainMenu, std::make_shared <Button>(ButtonType::StartButton)));
  ButtonVec.push_back(std::make_pair(State::MainMenu, std::make_shared <Button>(ButtonType::ShopButton)));
  ButtonVec.push_back(std::make_pair(State::MainMenu, std::make_shared <Button>(ButtonType::ExitButton)));

  int i = 1;
  for (auto& it : ButtonVec)
  {
    it.second->GetSprite().setPosition(600.f, 200.f * i);
    it.second->GetSprite().setScale(7.f, 7.f);
    i++;
  }
}

void Menu::Update()
{

}

void Menu::Click()
{
  for (auto& it : ButtonVec)
  {

    if (it.second->GetSprite().getGlobalBounds().contains(GameSettings::GetMousePos().x, GameSettings::GetMousePos().y))
    {
      switch (it.second->GetButtonType())
      {
      case StartButton:
        GameManager::GetGame()->GetShop()->Clear();
        GameSettings::SetState(State::Playing);
        GameManager::GetGame()->GetBot()->Init();
        break;
      case ShopButton:
        GameManager::GetGame()->GetShop()->ReInit();
        GameSettings::SetState(State::Shoping);
        break;
      case ExitButton:
        exit(0);
        break;
      }
    }
  }
}

void Menu::Draw()
{
  for (auto& it : ButtonVec)
      it.second->Draw();
}