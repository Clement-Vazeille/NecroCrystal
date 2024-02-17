#include "SwordSlash.h"
#include "../Utilities/Math.h"

SwordSlash::SwordSlash() :
	loopAnimation(100, 5, 16, 8)
{
	speed = 0.3f; //vitesse vers le bas
	faction = 2;
	scale = 4.f;
	damage = 25;
}

void SwordSlash::Load(sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellTarget, sf::Vector2i& windowDimensions)
{
	sprite.setTexture(texture);
	loopAnimation.SetTextureRect(sprite);
	hitbox.setSize(sprite.getGlobalBounds().getSize());
	sprite.setScale(sf::Vector2f(scale * (float)windowDimensions.x / 1920.0f, scale * (float)windowDimensions.y / 1080.0f));
	sprite.setPosition(initialPosition);

	target = spellTarget - (sf::Vector2f(texture.getSize()) * sprite.getScale().x / 2.0f); //dividing by 2 make that the target will be hit by the spell middle and not the spell top left corner
	direction = Math::normalizeVector(target - sprite.getPosition());

	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(-1);
	hitbox.setFillColor(sf::Color::Transparent);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());
}

void SwordSlash::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	sprite.setScale(scale * (float)windowDimensions.x / 1920.0f, scale * windowDimensions.y / 1080.0f); //make scale a variable
	sf::Vector2f movement = Math::windowNormalizeVector(Math::normalizeVector(direction) * speed * deltaTime, windowDimensions);
	cameraService.MoveSprite(sprite, movement);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());

	loopAnimation.Update(sprite, deltaTime);
}

sf::Sprite& SwordSlash::getSprite(void)
{
	// TODO: insérer une instruction return ici
}
