#include "LooseLoop.h"
#include <iostream>

LooseLoop::LooseLoop() :
	loseText(nullptr)
{
}

LooseLoop::~LooseLoop()
{
	if (loseText != nullptr)
		delete loseText;
}

void LooseLoop::initialize(sf::Vector2i& windowDimensions, TextManager& textManager)
{
	if (texture.loadFromFile("Assets/Menu/Menu.png"))
	{
		std::cout << "Game Over texture loaded successfully" << std::endl;
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
		sprite.setScale(2.5f*windowDimensions.x/1920.f,3.f*windowDimensions.y/1080.f);
		sprite.setPosition(windowDimensions.x/2.f,windowDimensions.y/2.f);
	}
	else
		std::cout << "Game Over texture failed to load" << std::endl;

	std::string text = "Game Over";
	loseText = textManager.MakeSentence(text);

	std::string retryButtonText("Retry");
	retryButton.Initialise(textManager.MakeSentence(retryButtonText), sf::Vector2f(windowDimensions.x * 0.40f, windowDimensions.y * 0.45f),
		sf::Vector2f(windowDimensions.x * 0.21f, windowDimensions.y * 0.12f), windowDimensions, sf::Vector2f(0.1f, 0.08f));

	std::string quitButtonText = "Quit";
	quitGameButton.Initialise(textManager.MakeSentence(quitButtonText), sf::Vector2f(windowDimensions.x * 0.43f, windowDimensions.y * 0.62f),
		sf::Vector2f(windowDimensions.x * 0.16f, windowDimensions.y * 0.12f), windowDimensions, sf::Vector2f(0.1f, 0.1f));
}

int LooseLoop::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	sprite.setScale(2.5f * windowDimensions.x / 1920.f, 3.f * windowDimensions.y / 1080.f); //TODO variable scale
	sprite.setPosition(windowDimensions.x / 2.f, windowDimensions.y / 2.f);

	loseText->Update(10.f * windowDimensions.x / 1980.f, sf::Vector2f(windowDimensions.x * 0.4f, windowDimensions.y * 0.38f)); //TODO separate x and y scales

	if (retryButton.Update(15.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
		return 2;

	if(quitGameButton.Update(15.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
		return 1;

	return 0;
}

void LooseLoop::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	loseText->Draw(window);

	retryButton.Draw(window);
	quitGameButton.Draw(window);
}