#include "Button.h"
#include "GameSettings.h"

Button::Button(ButtonType Type)
{
	this->Type = Type;
	FileName = TypeToString(Type);

	if (ButtonTexture.loadFromFile(Path + FileName + FileExt))
		ButtonSprite.setTexture(ButtonTexture);
}

sf::Sprite& Button::GetSprite()
{
	return ButtonSprite;
}

ButtonType Button::GetButtonType()
{
	return Type;
}

void Button::Draw()
{
	GameSettings::GetWindow().draw(ButtonSprite);
}

const std::string Button::TypeToString(ButtonType Type)
{
	if (Type == ButtonType::BuyButton)
		return "Buy";
	if (Type == ButtonType::SellButton)
		return "Sell";
	if (Type == ButtonType::ExitButton)
		return "Exit";
	if (Type == ButtonType::StartButton)
		return "Start";
	if (Type == ButtonType::ShopButton)
		return "Shop";
	if (Type == ButtonType::BackButton)
		return "Back";

	return "";
}