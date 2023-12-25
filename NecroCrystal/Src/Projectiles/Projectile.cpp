#include "Projectile.h"
#include "../Utilities/Math.h"

Projectile::Projectile() : speed(0.2f)
{
}

void Projectile::Load(sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellTarget)
{
	sprite.setTexture(texture);
	sprite.scale(sf::Vector2f(2.0f, 2.0f));
	sprite.setPosition(initialPosition);

	target = spellTarget - (sf::Vector2f(texture.getSize()) * sprite.getScale().x / 2.0f); //dividing by 2 make that the target will be hit by the spell middle and not the spell top left corner
	direction = Math::normalizeVector(target - sprite.getPosition());
}

void Projectile::Draw(sf::RenderWindow* window) const
{
	window->draw(sprite);
}
