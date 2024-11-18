#include "DeathLoop.h"

DeathLoop::DeathLoop() :
	necroCrystalText(nullptr),
	loopAnimation(2500.f/10.f,10,960,540),
	sceneDuration(2500.f),sceneTimer(0)
{
}

DeathLoop::~DeathLoop()
{
	if (necroCrystalText != nullptr)
		delete necroCrystalText;
}

void DeathLoop::Initialize(sf::Vector2i& windowDimensions, TextManager& textManager)
{
	if (texture.loadFromFile("Assets/Menu/DieScreen.png")) //TODO : Make a real scene
	{
		sprite.setTexture(texture);
		loopAnimation.SetTextureRect(sprite);
		sprite.setScale(2.f * windowDimensions.x / 1920.f, 2.f * windowDimensions.y / 1080.f);
		sprite.setPosition(0, 0);
	}

	std::string text = "You Died";
	necroCrystalText = textManager.MakeSentence(text);
}

bool DeathLoop::Update(float deltaTime, sf::Vector2i& windowDimensions)
{
	sprite.setScale(2.f * windowDimensions.x / 1920.f, 2.f * windowDimensions.y / 1080.f); //TODO variable scale
	sprite.setPosition(0, 0);

	necroCrystalText->Update(30.f * windowDimensions.x / 1980.f, sf::Vector2f(windowDimensions.x * 0.2f, windowDimensions.y * 0.33f)); //TODO separate x and y scales

	loopAnimation.Update(sprite, deltaTime);

	sceneTimer += deltaTime;
	if (sceneTimer >= sceneDuration)
	{
		this->Reset();
		return 1;
	}
	return 0;
}

void DeathLoop::Draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	necroCrystalText->Draw(window);
}

void DeathLoop::Reset(void)
{
	sceneTimer = 0;
	loopAnimation.Reset(sprite);
}
