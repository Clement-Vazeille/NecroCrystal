#include "HammerThrow.h"
#include "../../../Utilities/Math.h"

HammerThrow::HammerThrow() :
	loopAnimation(0,1,16,16)
{
	speed = 0.85f;
	faction = 2;
	scale = 4.f;
	damage = 15;
}
void HammerThrow::Load(const sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellTarget, sf::Vector2i& windowDimensions)
{
	this->Projectile::Load(texture, initialPosition, spellTarget, windowDimensions);
	loopAnimation.SetTextureRect(sprite);
	hitbox.setSize(sprite.getGlobalBounds().getSize() / scale);
}

void HammerThrow::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	sprite.setScale(scale * (float)windowDimensions.x / 1920.0f, scale * windowDimensions.y / 1080.0f); //make scale a variable
	sf::Vector2f movement = Math::windowNormalizeVector(Math::normalizeVector(direction) * speed * deltaTime, windowDimensions);
	cameraService.MoveSprite(sprite, movement);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());
	loopAnimation.Update(sprite, deltaTime);
}

sf::Sprite& HammerThrow::getSprite(void)
{
	return sprite;
}
