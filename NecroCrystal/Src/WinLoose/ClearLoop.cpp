#include "ClearLoop.h"
#include <iostream>

ClearLoop::ClearLoop() :
	clearText(nullptr)
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

void ClearLoop::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	sprite.setScale(2.5f * windowDimensions.x / 1920.f, 2.5f * windowDimensions.y / 1080.f); //TODO variable scale
	sprite.setPosition(windowDimensions.x / 2.f, windowDimensions.y / 2.f);

	clearText->Update(8.f * windowDimensions.x / 1980.f, sf::Vector2f(windowDimensions.x * 0.415f, windowDimensions.y * 0.53f)); //TODO separate x and y scales

}

void ClearLoop::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	clearText->Draw(window);
}
