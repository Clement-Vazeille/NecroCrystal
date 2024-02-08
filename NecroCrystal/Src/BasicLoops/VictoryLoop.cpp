#include "VictoryLoop.h"

VictoryLoop::VictoryLoop() :
	victoryText(nullptr),
	timerText(nullptr)
{
}

VictoryLoop::~VictoryLoop()
{
	if (victoryText != nullptr)
		delete victoryText;
	if (timerText != nullptr)
		delete timerText;
}

void VictoryLoop::initialize(sf::Vector2i& windowDimensions, TextManager& textManager)
{
	if (texture.loadFromFile("Assets/Menu/EndMenu.png"))
	{
		sprite.setTexture(texture);
		sprite.setScale(2.f * windowDimensions.x / 1920.f, 2.f * windowDimensions.y / 1080.f);
		sprite.setPosition(0,0);
	}

	std::string text = "Stage Cleared";
	victoryText = textManager.MakeSentence(text);

	std::string continueButtonText = "Main Menu";
	restartButton.Initialise(textManager.MakeSentence(continueButtonText), sf::Vector2f(windowDimensions.x * 0.38f, windowDimensions.y * 0.50f),
		sf::Vector2f(windowDimensions.x * 0.26f, windowDimensions.y * 0.1f), windowDimensions, sf::Vector2f(0.05f, 0.1f));

	std::string quitButtonText = "Quit";
	quitGameButton.Initialise(textManager.MakeSentence(quitButtonText), sf::Vector2f(windowDimensions.x * 0.44f, windowDimensions.y * 0.63f),
		sf::Vector2f(windowDimensions.x * 0.13f, windowDimensions.y * 0.1f), windowDimensions, sf::Vector2f(0.1f, 0.1f));

}

void VictoryLoop::setTimer(std::string timeText, TextManager& textManager)
{
	timerText = textManager.MakeSentence(timeText);
}

int VictoryLoop::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	sprite.setScale(2.f * windowDimensions.x / 1920.f, 2.f * windowDimensions.y / 1080.f); //TODO variable scale
	sprite.setPosition(0,0);

	victoryText->Update(7.f * windowDimensions.x / 1980.f, sf::Vector2f(windowDimensions.x * 0.39f, windowDimensions.y * 0.37f)); //TODO separate x and y scales
	timerText->Update(7.f * windowDimensions.x / 1980.f, sf::Vector2f(windowDimensions.x * 0.39f, windowDimensions.y * 0.45f));

	if (quitGameButton.Update(12.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
		return 1;
	if (restartButton.Update(12.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
		return 2;

	return 0;
}

void VictoryLoop::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	victoryText->Draw(window);
	timerText->Draw(window);

	restartButton.Draw(window);
	quitGameButton.Draw(window);
}
