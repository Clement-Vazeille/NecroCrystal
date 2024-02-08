#include "MainMenuLoop.h"

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

	if (texture.loadFromFile("Assets/Menu/Menu.png")) //TODO : Make a real scene
	{
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
		sprite.setScale(2.5f * windowDimensions.x / 1920.f, 3.f * windowDimensions.y / 1080.f);
		sprite.setPosition(windowDimensions.x / 2.f, windowDimensions.y / 2.f);
	}

	std::string text = "NecroCrystal";
	necroCrystalText = textManager.MakeSentence(text);

	std::string retryButtonText("Start Game");
	startButton.Initialise(textManager.MakeSentence(retryButtonText), sf::Vector2f(windowDimensions.x * 0.40f, windowDimensions.y * 0.45f),
		sf::Vector2f(windowDimensions.x * 0.21f, windowDimensions.y * 0.12f), windowDimensions, sf::Vector2f(0.1f, 0.08f));

	std::string quitButtonText = "Quit Game";
	quitGameButton.Initialise(textManager.MakeSentence(quitButtonText), sf::Vector2f(windowDimensions.x * 0.43f, windowDimensions.y * 0.62f),
		sf::Vector2f(windowDimensions.x * 0.16f, windowDimensions.y * 0.12f), windowDimensions, sf::Vector2f(0.1f, 0.1f));
}

int MainMenuLoop::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	sprite.setScale(2.5f * windowDimensions.x / 1920.f, 3.f * windowDimensions.y / 1080.f); //TODO variable scale
	sprite.setPosition(windowDimensions.x / 2.f, windowDimensions.y / 2.f);

	necroCrystalText->Update(10.f * windowDimensions.x / 1980.f, sf::Vector2f(windowDimensions.x * 0.4f, windowDimensions.y * 0.38f)); //TODO separate x and y scales

	if (startButton.Update(15.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
		return 2;

	if (quitGameButton.Update(15.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
		return 1;

	return 0;
}

void MainMenuLoop::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	necroCrystalText->Draw(window);

	startButton.Draw(window);
	quitGameButton.Draw(window);
}
