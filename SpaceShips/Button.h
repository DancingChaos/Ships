#pragma once
#include <SFML/Graphics.hpp>

enum ButtonType
{
	StartButton,
	ShopButton,
	ExitButton,
	BuyButton,
	SellButton,
	BackButton
};

class Button
{
public:
	Button(ButtonType Type);

	void Draw();
	ButtonType GetButtonType();
	sf::Sprite& GetSprite();

private:
	const std::string TypeToString(ButtonType Type);
	sf::Texture ButtonTexture;
	sf::Sprite ButtonSprite;

	ButtonType Type;

	std::string FileName;
	const std::string Path="..\\Images\\";
	const std::string FileExt=".png";
};

