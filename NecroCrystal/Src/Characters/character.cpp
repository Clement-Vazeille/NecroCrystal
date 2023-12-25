#include "character.h"

Character::Character() : 
	health(0),width(0),height(0),scale(0),
	speed(0),faction(0),
	sprites(nullptr),spriteNumber(0)
{
}

Character::~Character()
{
}

void Character::SetHealth(int hp)
{
	health = hp;
}

int Character::GetHealth(void) const
{
	return health;
}

void Character::Draw(sf::RenderWindow* window) const
{
	for (size_t i=0;i<spriteNumber;i++)
	{
		window->draw(sprites[i]);
	}
}

sf::Sprite& Character::getSprite(void) const   //TODO changer pour remplacer par les hitboxes
{
	return sprites[0];
}

int Character::getFaction(void) const
{
	return faction;
}
