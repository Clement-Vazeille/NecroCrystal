#include "DarkProjectile.h"


void DarkProjectile::Load(sf::Texture& texture)
{
	sprite.setTexture(texture);
	sprite.scale(sf::Vector2f(2.0f, 2.0f));
}

void DarkProjectile::Update()
{
}

void DarkProjectile::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
