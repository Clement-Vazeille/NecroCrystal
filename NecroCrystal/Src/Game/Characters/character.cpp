#include "character.h"

Character::Character() :
	width(0), height(0), scale(0),
	speed(0), faction(0), health(0), maxHealth(0), spriteNumber(0),
	damageMultiplier(1.f)
{
}

Character::~Character()
{
	//delete(sprites); //fait crash le programme ????
}

bool Character::TakeDamage(int damage)
{
	health -= damage*damageMultiplier;
	return(health<=0);
}

const int Character::GetSerial(void) const
{
	return 0;
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

void Character::DrawHitbox(sf::RenderWindow* window) const
{
	window->draw(hitbox);
}

const sf::Sprite& Character::getSprite(void) const   //devrait techniquement plus être utilisé
{
	return sprites[0];
}

int Character::getFaction(void) const
{
	return faction;
}

void Character::Activate(void)
{
}

sf::RectangleShape* Character::getHitbox(void)
{
	return &hitbox;
}