#include "HitboxDisplay.h"
#include <SFML/Graphics.hpp>

HitboxDisplay::HitboxDisplay() : 
	value(false), timer(0), refreshRate(300)
{
}

void HitboxDisplay::Update(float deltaTime)
{
	timer += deltaTime;
	if (timer > refreshRate)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F10))
		{
			timer = 0;
			value = !value;
		}
	}
}

bool HitboxDisplay::getValue(void) const
{
	return value;
}
