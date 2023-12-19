#include "FrameRate.h"
#include <iostream>

FrameRate::FrameRate() : 
	timer(0),refreshTime(1000)
{
}

FrameRate::~FrameRate()
{
}

void FrameRate::Initialize()
{
}

void FrameRate::Load()
{
	if (font.loadFromFile("Assets/Fonts/arial.ttf"))
	{
		std::cout << "Arial.ttf font has been loaded successfully"<<std::endl;
		text.setFont(font);
	}
	else
	{
		std::cout << "Faile to load Arial.ttf" << std::endl;
	}
}

void FrameRate::Update(float deltaTime)
{
	timer += deltaTime;
	if (timer > refreshTime)
	{
		timer = 0;
		std::string frameRateString = "FPS: " + std::to_string((int)(1000.0f / deltaTime))
			+ " frameTime: " + std::to_string((int)deltaTime);
		text.setString(frameRateString);
	}
	
}

void FrameRate::Draw(sf::RenderWindow& window)
{
	window.draw(text);
}


