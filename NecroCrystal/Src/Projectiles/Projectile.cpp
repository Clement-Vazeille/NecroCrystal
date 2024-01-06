#include "Projectile.h"
#include "../Utilities/Math.h"
#include "iostream"

Projectile::Projectile() : speed(0.2f),faction(0)
{
}

void Projectile::Load(sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellTarget, sf::Vector2i& windowDimensions)
{
	sprite.setTexture(texture);
	hitbox.setSize(sprite.getGlobalBounds().getSize());
	sprite.setScale(sf::Vector2f(scale*(float)windowDimensions.x/1920.0f, scale*(float)windowDimensions.y/1080.0f));
	sprite.setPosition(initialPosition);

	target = spellTarget - (sf::Vector2f(texture.getSize()) * sprite.getScale().x / 2.0f); //dividing by 2 make that the target will be hit by the spell middle and not the spell top left corner
	direction = Math::normalizeVector(target - sprite.getPosition());

	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(-1);
	hitbox.setFillColor(sf::Color::Transparent);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());
}

void Projectile::Draw(sf::RenderWindow* window, bool drawHitbox) const
{
	window->draw(sprite);
	if(drawHitbox)
		window->draw(hitbox);
}
int Projectile::getFaction(void) const
{
	return faction;
}

sf::RectangleShape* Projectile::getHitbox(void)
{
	return &hitbox;
}
