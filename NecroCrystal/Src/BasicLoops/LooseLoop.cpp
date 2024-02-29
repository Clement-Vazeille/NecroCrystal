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
		sprite.setScale(2.5f*windowDimensions.x/1920.f,4.6f*windowDimensions.y/1080.f);
		sprite.setPosition(windowDimensions.x*0.47,windowDimensions.y/2.f);
	}
	else
		std::cout << "Game Over texture failed to load" << std::endl;

	std::string text = "Game Over";
	loseText = textManager.MakeSentence(text);

	std::string retryButtonText("Retry");
	retryButton.Initialise(textManager.MakeSentence(retryButtonText), sf::Vector2f(windowDimensions.x * 0.405f, windowDimensions.y * 0.38f),
		sf::Vector2f(windowDimensions.x * 0.20f, windowDimensions.y * 0.12f), windowDimensions, sf::Vector2f(0.1f, 0.08f));
	
	std::string mainMenuButtontext = "MainMenu";
	mainMenuButton.Initialise(textManager.MakeSentence(mainMenuButtontext), sf::Vector2f(windowDimensions.x * 0.382f, windowDimensions.y * 0.52f),
		sf::Vector2f(windowDimensions.x * 0.248f, windowDimensions.y * 0.12f), windowDimensions, sf::Vector2f(0.035f, 0.1f));

	std::string quitButtonText = "Quit";
	quitGameButton.Initialise(textManager.MakeSentence(quitButtonText), sf::Vector2f(windowDimensions.x * 0.435f, windowDimensions.y * 0.66f),
		sf::Vector2f(windowDimensions.x * 0.15f, windowDimensions.y * 0.12f), windowDimensions, sf::Vector2f(0.1f, 0.1f));
}

int LooseLoop::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	sprite.setScale(2.5f * windowDimensions.x / 1920.f, 3.f * windowDimensions.y / 1080.f); //TODO variable scale
	sprite.setPosition(windowDimensions.x / 2.f, windowDimensions.y / 2.f);

	loseText->Update(11.f * windowDimensions.x / 1980.f, sf::Vector2f(windowDimensions.x * 0.39f, windowDimensions.y * 0.34f)); //TODO separate x and y scales

	if (retryButton.Update(14.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
	{
		retryButton.Reset();
		quitGameButton.Reset();
		mainMenuButton.Reset();
		return 2;
	}

	if (mainMenuButton.Update(12.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
	{
		retryButton.Reset();
		quitGameButton.Reset();
		mainMenuButton.Reset();
		return 3;
	}

	if(quitGameButton.Update(14.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
		return 1;

	return 0;
}

void LooseLoop::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	loseText->Draw(window);

	retryButton.Draw(window);
	mainMenuButton.Draw(window);
	quitGameButton.Draw(window);
}