#include "Explosion.h"
#include "../../../Utilities/Math.h"

ExplosionProj::ExplosionProj():
	lifeSpan(800),liveTimer(0)
{
	speed = 0.2f;
	faction = 2;
	scale = 10.f;
	damage = 25;
}

void ExplosionProj::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	liveTimer += deltaTime;

	sprite.setScale(scale * (float)windowDimensions.x / 1920.0f, scale * windowDimensions.y / 1080.0f);
	sf::Vector2f movement = sf::Vector2f(0, 0);
	cameraService.MoveSprite(sprite, movement);

	//hitbox.setScale(sprite.getScale());
	//hitbox.setPosition(sprite.getGlobalBounds().getPosition());
	hitbox.setScale(sprite.getScale().x * 0.6, sprite.getScale().y * 0.6);
	hitbox.setPosition(sprite.getGlobalBounds().getPosition()
		+ Math::windowNormalizeVector(sf::Vector2f(sprite.getGlobalBounds().width * 0.2, sprite.getGlobalBounds().height * 0.2), windowDimensions));
}

sf::Sprite& ExplosionProj::getSprite(void)
{
	return sprite;
}

bool ExplosionProj::ShouldBeDestroyed(void) const
{
	return liveTimer >= lifeSpan;
}
