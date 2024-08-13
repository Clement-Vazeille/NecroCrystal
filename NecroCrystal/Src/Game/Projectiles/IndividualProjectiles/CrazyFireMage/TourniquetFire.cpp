#include "TourniquetFire.h"
#include "../../../Utilities/Math.h"

TourniquetFire::TourniquetFire() :
	loopAnimation(550.f / 4.f, 4, 8, 8)
{
	speed = 0.3f;
	faction = 2;
	scale = 5.f;
	damage = 4;
}

void TourniquetFire::Load(const sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellDirection, sf::Vector2i& windowDimensions)
{
	this->Projectile::Load(texture, initialPosition, spellDirection, windowDimensions);
	loopAnimation.SetTextureRect(sprite);
	hitbox.setSize(sprite.getGlobalBounds().getSize() / scale);
	direction = spellDirection;
	
}

void TourniquetFire::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{

	sprite.setScale(scale * (float)windowDimensions.x / 1920.0f, scale * windowDimensions.y / 1080.0f);
	sf::Vector2f movement = Math::windowNormalizeVector(Math::normalizeVector(direction) * speed * deltaTime, windowDimensions);
	cameraService.MoveSprite(sprite, movement);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());
	loopAnimation.Update(sprite, deltaTime);
}

sf::Sprite& TourniquetFire::getSprite(void)
{
	return sprite;
}

bool TourniquetFire::ShouldBeDestroyed(void) const
{
	return false;
}
