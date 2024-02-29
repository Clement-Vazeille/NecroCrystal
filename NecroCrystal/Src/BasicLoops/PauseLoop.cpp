#include "PauseLoop.h"
#include <iostream>
#include <string>

PauseLoop::PauseLoop() :
	pauseText(nullptr)
{
}

PauseLoop::~PauseLoop()
{
	if(pauseText != nullptr)
		delete(pauseText);
}

void PauseLoop::initialize(sf::Vector2i& windowDimensions,TextManager& textManager)
{
	if (texture.loadFromFile("Assets/Menu/Menu.png"))
	{
		std::cout << "Pause texture loaded successfully" << std::endl;
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
		sprite.setScale(2.5f * windowDimensions.x / 1920.f, 2.5f * windowDimensions.y / 1080.f);
		sprite.setPosition(windowDimensions.x *0.55f, windowDimensions.y / 2.f);
	}
	else
		std::cout << "Pause texture failed to load" << std::endl;
	std::string text = "Pause";
	pauseText = textManager.MakeSentence(text);

	std::string buttontext = "Quit";
	quitGameButton.Initialise(textManager.MakeSentence(buttontext),sf::Vector2f(windowDimensions.x*0.43f,windowDimensions.y*0.61f), 
		sf::Vector2f(windowDimensions.x * 0.15f, windowDimensions.y * 0.12f),windowDimensions,sf::Vector2f(0.1f,0.1f));

	std::string mainMenuButtontext = "MainMenu";
	mainMenuButton.Initialise(textManager.MakeSentence(mainMenuButtontext), sf::Vector2f(windowDimensions.x * 0.382f, windowDimensions.y * 0.46f),
		sf::Vector2f(windowDimensions.x * 0.248f, windowDimensions.y * 0.12f), windowDimensions, sf::Vector2f(0.035f, 0.1f));
}

int PauseLoop::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	sprite.setScale(2.5f * windowDimensions.x / 1920.f, 2.5f * windowDimensions.y / 1080.f); //TODO variable scale
	sprite.setPosition(windowDimensions.x / 2.f, windowDimensions.y / 2.f);

	pauseText->Update(15.f*windowDimensions.x/1980.f, sf::Vector2f(windowDimensions.x*0.415f,windowDimensions.y*0.43f)); //TODO separate x and y scales
	if (quitGameButton.Update(15.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
		return 1;

	if (mainMenuButton.Update(12.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
	{
		this->ResetButton();
		return 2;
	}

	return 0;
}

void PauseLoop::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	pauseText->Draw(window);
	quitGameButton.Draw(window);
	mainMenuButton.Draw(window);
}

void PauseLoop::ResetButton(void)
{
	quitGameButton.Reset();
	mainMenuButton.Reset();
}
