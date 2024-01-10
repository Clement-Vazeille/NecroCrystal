#include "PauseLoop.h"
#include <iostream>

PauseLoop::PauseLoop() :
	pauseText(nullptr)
{
}

PauseLoop::~PauseLoop()
{
}

void PauseLoop::initialize(sf::Vector2i& windowDimensions,TextManager& textManager)
{
	if (texture.loadFromFile("Assets/Menu/Pause.png"))
	{
		std::cout << "Pause texture loaded successfully" << std::endl;
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
		sprite.setScale(2.5f * windowDimensions.x / 1920.f, 2.5f * windowDimensions.y / 1080.f);
		sprite.setPosition(windowDimensions.x / 2.f, windowDimensions.y / 2.f);
	}
	else
		std::cout << "Pause texture failed to load" << std::endl;
}

void PauseLoop::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	sprite.setScale(2.5f * windowDimensions.x / 1920.f, 2.5f * windowDimensions.y / 1080.f); //TODO variable scale
	sprite.setPosition(windowDimensions.x / 2.f, windowDimensions.y / 2.f);
}

void PauseLoop::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}
