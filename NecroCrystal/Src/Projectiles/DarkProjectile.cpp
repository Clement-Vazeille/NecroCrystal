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

	target = spellTarget-(sf::Vector2f(texture.getSize())*sprite.getScale().x / 2.0f); //dividing by 2 make that the target will be hit by the spell middle and not the spell top left corner
	direction = Math::normalizeVector(target - sprite.getPosition());

	//std::cout << "Direction non normale : " << std::endl << "X: " << (target - sprite.getPosition()).x << std::endl << "Y: " << (target - sprite.getPosition()).y << std::endl;
}

void DarkProjectile::Update(float deltaTime,CameraService& cameraService)
{
	sf::Vector2f movement = Math::normalizeVector(direction) * speed * deltaTime;
	cameraService.MoveSprite(sprite, movement);
}

void DarkProjectile::Draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}
