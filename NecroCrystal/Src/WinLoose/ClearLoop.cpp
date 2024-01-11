#include "ClearLoop.h"
#include <iostream>

ClearLoop::ClearLoop() :
	clearText(nullptr),
	timerText(nullptr)
{
}

ClearLoop::~ClearLoop()
{
}

void ClearLoop::initialize(sf::Vector2i& windowDimensions, TextManager& textManager)
{
	if (texture.loadFromFile("Assets/Menu/levelCleared.png"))
	{
		std::cout << "Level Cleared texture loaded successfully" << std::endl;
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
		sprite.setScale(2.5f * windowDimensions.x / 1920.f, 2.5f * windowDimensions.y / 1080.f);
		sprite.setPosition(windowDimensions.x / 2.f, windowDimensions.y / 2.f);
	}
	else
		std::cout << "Level Cleared texture failed to load" << std::endl;

	std::string text = "Stage Cleared";
	clearText = textManager.MakeSentence(text);
}

void ClearLoop::setTimer(std::string timeText, TextManager& textManager)
{
	timerText = textManager.MakeSentence(timeText);
}

void ClearLoop::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	sprite.setScale(2.5f * windowDimensions.x / 1920.f, 2.5f * windowDimensions.y / 1080.f); //TODO variable scale
	sprite.setPosition(windowDimensions.x / 2.f, windowDimensions.y / 2.f);

	clearText->Update(7.f * windowDimensions.x / 1980.f, sf::Vector2f(windowDimensions.x * 0.39f, windowDimensions.y * 0.45f)); //TODO separate x and y scales
	timerText->Update(7.f * windowDimensions.x / 1980.f, sf::Vector2f(windowDimensions.x * 0.39f, windowDimensions.y * 0.55f));
}

void ClearLoop::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	clearText->Draw(window);
	timerText->Draw(window);
}
