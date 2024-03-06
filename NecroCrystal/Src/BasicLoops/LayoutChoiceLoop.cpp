#include "LayoutChoiceLoop.h"

LayoutChoiceLoop::LayoutChoiceLoop() :
	necroCrystalText(nullptr)
{
}

LayoutChoiceLoop::~LayoutChoiceLoop()
{
	if (necroCrystalText != nullptr)
		delete necroCrystalText;
}

void LayoutChoiceLoop::initialize(sf::Vector2i& windowDimensions, TextManager& textManager)
{
	if (texture.loadFromFile("Assets/Menu/KeyboardLayout.png")) //TODO : Make a real scene
	{
		sprite.setTexture(texture);
		sprite.setScale(2.f * windowDimensions.x / 1920.f, 2.f * windowDimensions.y / 1080.f);
		sprite.setPosition(0, 0);
	}

	std::string text = "Keyboard Layout";
	necroCrystalText = textManager.MakeSentence(text);

	std::string retryButtonText("Azerty");
	azertyButton.Initialise(textManager.MakeSentence(retryButtonText), sf::Vector2f(windowDimensions.x * 0.1f, windowDimensions.y * 0.6f),
		sf::Vector2f(windowDimensions.x * 0.33f, windowDimensions.y * 0.18f), windowDimensions, sf::Vector2f(0.07f, 0.08f));

	std::string tutorialButtonText = "Qwerty";
	qwertyButton.Initialise(textManager.MakeSentence(tutorialButtonText), sf::Vector2f(windowDimensions.x * 0.57f, windowDimensions.y * 0.6f),
		sf::Vector2f(windowDimensions.x * 0.33f, windowDimensions.y * 0.18f), windowDimensions, sf::Vector2f(0.07f, 0.1f));

}

int LayoutChoiceLoop::update(float deltaTime, sf::Vector2i& windowDimensions, sf::Vector2f& mousePosition)
{
	sprite.setScale(2.f * windowDimensions.x / 1920.f, 2.f * windowDimensions.y / 1080.f); //TODO variable scale
	sprite.setPosition(0, 0);

	necroCrystalText->Update(23.f * windowDimensions.x / 1980.f, sf::Vector2f(windowDimensions.x * 0.07f, windowDimensions.y * 0.35f)); //TODO separate x and y scales

	if (azertyButton.Update(20.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
		return 1;

	if (qwertyButton.Update(20.f * windowDimensions.x / 1980.f, windowDimensions, mousePosition))
		return 2;

	return 0;
}

void LayoutChoiceLoop::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	necroCrystalText->Draw(window);

	qwertyButton.Draw(window);
	azertyButton.Draw(window);
}
