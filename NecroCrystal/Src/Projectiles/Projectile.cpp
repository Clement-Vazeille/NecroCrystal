#include "Projectile.h"
#include "../Utilities/Math.h"

Projectile::Projectile() : speed(0.2f),faction(0)
{
}

void Projectile::Load(sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellTarget, sf::Vector2i& windowDimensions)
{
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(2.5f*(float)windowDimensions.x/1920.0f, 2.5f*(float)windowDimensions.y/1080.0f));
	sprite.setPosition(initialPosition);

	target = spellTarget - (sf::Vector2f(texture.getSize()) * sprite.getScale().x / 2.0f); //dividing by 2 make that the target will be hit by the spell middle and not the spell top left corner
	direction = Math::normalizeVector(target - sprite.getPosition());
}

void Projectile::Draw(sf::RenderWindow* window) const
{
	window->draw(sprite);
}
int Projectile::getFaction(void) const
{
	return faction;
}
