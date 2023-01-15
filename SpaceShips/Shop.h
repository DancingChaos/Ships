#pragma once
#include "Button.h"
#include "GameSettings.h"
#include "Ship.h"
#include "Player.h"

class Shop
{
public:
	void Init();
	void Click();
	void Update();
	void Draw();
	void SelectItem();
	void Clear();
	void ReInit();
	std::pair<Ship *, const int> CreateShipByType(ShipType Type);
private:
	ShipType ShipToAction;

	sf::RectangleShape ShipToBuyRect;
	sf::Text MoneyCount;


	std::vector<std::pair<State, std::shared_ptr<Button>>> ShopButtonVec;
	std::vector<std::pair<Ship *, sf::Text*>> ShipStock;

	sf::Texture MoneyTexture;
	sf::Sprite MoneySprite;

	sf::Font Aerial;
};

