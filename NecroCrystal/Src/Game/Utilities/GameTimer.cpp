#include "GameTimer.h"

GameTimer::GameTimer() :
	timerText(nullptr)
{
}

void GameTimer::Initialize(TextManager& textManager)
{
	std::string emptyText = "                           ";
	timerText = textManager.MakeSentence(emptyText);
}

void GameTimer::Update(sf::Vector2i& windowDimensions, std::string string)
{
	timerText->ChangeText(string);
	timerText->Update(7.f * windowDimensions.x / 1980.f, sf::Vector2f(windowDimensions.x * 0.39f, windowDimensions.y * 0.05f));
}

void GameTimer::Draw(sf::RenderWindow* window)
{
	timerText->Draw(window);
}
