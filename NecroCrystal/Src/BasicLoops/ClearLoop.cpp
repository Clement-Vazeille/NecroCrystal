#include "ClearLoop.h"
#include <iostream>

ClearLoop::ClearLoop() :
	clearText(nullptr),
	timerText(nullptr)
{
}

ClearLoop::~ClearLoop()
{
	if (clearText != nullptr)
		delete clearText;
	if (timerText != nullptr)
		delete timerText;
}

void ClearLoop::initialize(sf::Vector2i& windowDimensions, TextManager& textManager)
{
	if (texture.loadFromFile("Assets/Menu/Menu.png"))
	{
		std::cout << "Level Cleared texture loaded successfully" << std::endl;
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
		sprite.setScale(2.5f * windowDimensions.x / 1920.f, 3.f * windowDimensions.y / 1080.f);
		sprite.setPosition(windowDimensions.x / 2.f, windowDimensions.y / 2.f);
	}
	else
		std::cout << "Level Cleared texture failed to load" << std::endl;

	std::string text = "Stage Cleared";
	clearText = textManager.MakeSentence(text);

	std::string buttontext = "Quit";
	quitGameButton.Initialise(textManager.MakeSentence(buttontext), sf::Vector2f(windowDimensions.x * 0.43f, windowDimensions.y * 0.60f),
		sf::Vector2f(windowDimensions.x * 0.15f, windowDimensions.y * 0.12f), windowDimensions, sf::Vector2f(0.1f, 0.1f));

}

void ClearLoop::setTimer(std::string timeText, TextManager& textManager)
{
	timerText = textManager.MakeSentence(timeText);
}

int ClearLoop::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	sprite.setScale(2.5f * windowDimensions.x / 1920.f, 2.5f * windowDimensions.y / 1080.f); //TODO variable scale
	sprite.setPosition(windowDimensions.x / 2.f, windowDimensions.y / 2.f);

	clearText->Update(7.f * windowDimensions.x / 1980.f, sf::Vector2f(windowDimensions.x * 0.39f, windowDimensions.y * 0.45f)); //TODO separate x and y scales
	timerText->Update(7.f * windowDimensions.x / 1980.f, sf::Vector2f(windowDimensions.x * 0.39f, windowDimensions.y * 0.55f));

	if (quitGameButton.Update(15.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
		return 1;

	return 0;
}

void ClearLoop::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	clearText->Draw(window);
	timerText->Draw(window);

	quitGameButton.Draw(window);
}
