#include "FrameRate.h"
#include <iostream>

FrameRate::FrameRate() : 
	timer(0),refreshTime(500.0),
	displayed(true),displayTimer(0),displayRefreshTime(250.0),
	fpsNumber(0),fpsSum(0)
{
}

FrameRate::~FrameRate()
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


void FrameRate::Update(double deltaTime)
{
	
	if (displayTimer < displayRefreshTime)
	{
		displayTimer += deltaTime;
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			displayed = !displayed;
			timer = 0;
			displayTimer = 0;
		}
	}
	if (displayed)
	{
		fpsSum += 1000.0f / deltaTime;
		fpsNumber++;
		timer += deltaTime;
		if (timer > refreshTime)
		{
			timer = 0;
			std::string frameRateString = "FPS: " + std::to_string((int)(fpsSum/fpsNumber));
			text.setString(frameRateString);
			fpsNumber = 0;
			fpsSum = 0;
		}
	}
	
}

void FrameRate::Draw(sf::RenderWindow* window)
{
	if(displayed)
		window->draw(text);
}


