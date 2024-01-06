#include "LooseLoop.h"
#include <iostream>

LooseLoop::LooseLoop()
{
}

LooseLoop::~LooseLoop()
{
}

void LooseLoop::initialize(sf::Vector2i& windowDimensions)
{
	if (texture.loadFromFile("Assets/Menu/gameOver.png"))
	{
		std::cout << "Game Over texture loaded successfully" << std::endl;
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
		sprite.setScale(2.5f*windowDimensions.x/1920.f,2.5f*windowDimensions.y/1080.f);
		sprite.setPosition(windowDimensions.x/2.f,windowDimensions.y/2.f);
	}
	else
		std::cout << "Game Over texture failed to load" << std::endl;
}

void LooseLoop::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	sprite.setScale(2.5f * windowDimensions.x / 1920.f, 2.5f * windowDimensions.y / 1080.f); //TODO variable scale
	sprite.setPosition(windowDimensions.x / 2.f, windowDimensions.y / 2.f);
}

void LooseLoop::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}