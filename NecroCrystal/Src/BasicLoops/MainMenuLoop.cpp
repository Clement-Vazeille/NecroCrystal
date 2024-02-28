#include "MainMenuLoop.h"
#include <iostream>

void MainMenuLoop::ResetButtons(void)
{
	startButton.Reset();
	tutorialButton.Reset();
	quitGameButton.Reset();
}

MainMenuLoop::MainMenuLoop() :
	necroCrystalText(nullptr)
{
}

MainMenuLoop::~MainMenuLoop()
{
	if (necroCrystalText != nullptr)
		delete necroCrystalText;
}

void MainMenuLoop::initialize(sf::Vector2i& windowDimensions, TextManager& textManager)
{

	if (texture.loadFromFile("Assets/Menu/MainMenu.png")) //TODO : Make a real scene
	{
		sprite.setTexture(texture);
		sprite.setScale(2.f * windowDimensions.x / 1920.f, 2.f * windowDimensions.y / 1080.f);
		sprite.setPosition(0,0);
	}

	std::string text = "NecroCrystal";
	necroCrystalText = textManager.MakeSentence(text);

	std::string retryButtonText("Start Game");
	startButton.Initialise(textManager.MakeSentence(retryButtonText), sf::Vector2f(windowDimensions.x * 0.55f, windowDimensions.y * 0.35f),
		sf::Vector2f(windowDimensions.x * 0.36f, windowDimensions.y * 0.12f), windowDimensions, sf::Vector2f(0.07f, 0.08f));

	std::string tutorialButtonText = "Tutorial";
	tutorialButton.Initialise(textManager.MakeSentence(tutorialButtonText), sf::Vector2f(windowDimensions.x * 0.55f, windowDimensions.y * 0.52f),
		sf::Vector2f(windowDimensions.x * 0.28f, windowDimensions.y * 0.12f), windowDimensions, sf::Vector2f(0.07f, 0.1f));

	std::string quitButtonText = "Quit Game";
	quitGameButton.Initialise(textManager.MakeSentence(quitButtonText), sf::Vector2f(windowDimensions.x * 0.55f, windowDimensions.y * 0.70f),
		sf::Vector2f(windowDimensions.x * 0.32f, windowDimensions.y * 0.12f), windowDimensions, sf::Vector2f(0.07f, 0.1f));
}

int MainMenuLoop::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	sprite.setScale(2.f * windowDimensions.x / 1920.f, 2.f * windowDimensions.y / 1080.f); //TODO variable scale
	sprite.setPosition(0,0);

	necroCrystalText->Update(25.f * windowDimensions.x / 1980.f, sf::Vector2f(windowDimensions.x * 0.08f, windowDimensions.y * 0.27f)); //TODO separate x and y scales

	if (startButton.Update(13.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
	{
		this->ResetButtons();
		return 2;
	}
	if (tutorialButton.Update(13.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
	{
		this->ResetButtons();
		return 3;
	}
	if (quitGameButton.Update(13.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
		return 1;

	return 0;
}

void MainMenuLoop::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	necroCrystalText->Draw(window);

	startButton.Draw(window);
	tutorialButton.Draw(window);
	quitGameButton.Draw(window);
}
