#include "DashFire.h"
#include "../../../Utilities/Math.h"

DashFire::DashFire():
	loopAnimation(550.f / 4.f, 4, 8, 8),
	lifeSpan(5000),liveTimer(0)
{
	speed = 0.2f;
	faction = 2;
	scale = 3.f;
	damage = 5;
}

void DashFire::Load(const sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellTarget, sf::Vector2i& windowDimensions)
{
	this->Projectile::Load(texture, initialPosition, spellTarget, windowDimensions);
	loopAnimation.SetTextureRect(sprite);
	hitbox.setSize(sprite.getGlobalBounds().getSize() / scale);
}

void DashFire::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	liveTimer += deltaTime;

	sprite.setScale(scale * (float)windowDimensions.x / 1920.0f, scale * windowDimensions.y / 1080.0f); 
	sf::Vector2f movement =sf::Vector2f(0,0);
	cameraService.MoveSprite(sprite, movement);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());
	loopAnimation.Update(sprite, deltaTime);
}

sf::Sprite& DashFire::getSprite(void)
{
	return sprite;
}

bool DashFire::ShouldBeDestroyed(void) const
{
	return liveTimer >= lifeSpan;
}
