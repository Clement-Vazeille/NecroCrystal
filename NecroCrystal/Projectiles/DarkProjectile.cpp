#include "DarkProjectile.h"
#include "../Utilities/Math.h"
#include <iostream>

DarkProjectile::DarkProjectile() : 
	speed(0.5f)
{

}

void DarkProjectile::Load(sf::Texture& texture,const sf::Vector2f& initialPosition,sf::Vector2f& spellTarget)
{
	sprite.setTexture(texture);
	sprite.scale(sf::Vector2f(2.0f, 2.0f));
	sprite.setPosition(initialPosition);

	target = spellTarget;
	direction = Math::normalizeVector(target - sprite.getPosition());

	//std::cout << "Direction non normale : " << std::endl << "X: " << (target - sprite.getPosition()).x << std::endl << "Y: " << (target - sprite.getPosition()).y << std::endl;
}

void DarkProjectile::Update(float deltaTime)
{
	sprite.setPosition(sprite.getPosition() + Math::normalizeVector(direction) * speed * deltaTime);
}

void DarkProjectile::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
