#include "character.h"

Character::Character() : health(0),width(0),height(0),scale(0),speed(0)
{
}

Character::~Character()
{
}

void Character::SetHealth(int hp)
{
	health = hp;
}

void Character::Draw(sf::RenderWindow* window) const
{
	for (size_t i=0;i<spriteNumber;i++)
	{
		window->draw(sprites[i]);
	}
}
