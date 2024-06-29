#include "WallFire.h"

WallFire::WallFire() :
	loopAnimation(550.f / 4.f, 4, 8, 8),
	lifeSpan(2500), liveTimer(0)
{
	speed = 0.2f;
	faction = 2;
	scale = 3.f;
	damage = 7;
}

void WallFire::Load(const sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellTarget,sf::Vector2f mageSpeed, sf::Vector2i& windowDimensions)
{
	this->Projectile::Load(texture, initialPosition, spellTarget, windowDimensions);
	loopAnimation.SetTextureRect(sprite);
	hitbox.setSize(sprite.getGlobalBounds().getSize() / scale);
	mageSpeed = mageSpeed;
}

void WallFire::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	liveTimer += deltaTime;

	sprite.setScale(scale * (float)windowDimensions.x / 1920.0f, scale * windowDimensions.y / 1080.0f);
	sf::Vector2f movement = sf::Vector2f(0, 0);
	cameraService.MoveSprite(sprite, movement);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());
	loopAnimation.Update(sprite, deltaTime);
}

sf::Sprite& WallFire::getSprite(void)
{
	return sprite;
}

bool WallFire::ShouldBeDestroyed(void) const
{
	return liveTimer >= lifeSpan;
}
