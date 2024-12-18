#include "PoisonDot.h"
#include "../../../Utilities/Math.h"

PoisonDot::PoisonDot() :
	loopAnimation(0, 1, 8, 8),aliveTime(0.f)
{
	speed = 1.1f;
	faction = 2;
	scale = 2.f;
	damage = 3;
}

void PoisonDot::InverseTrajectory(void)
{
	targetDrift = -targetDrift;
}

void PoisonDot::Load(const sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellTarget, sf::Vector2i& windowDimensions)
{
	this->Projectile::Load(texture, initialPosition, spellTarget, windowDimensions);
	loopAnimation.SetTextureRect(sprite);
	hitbox.setSize(sprite.getGlobalBounds().getSize() / scale);
	
	spawnPosition = initialPosition;

	sf::Vector2f trajectory = target - initialPosition;
	targetDrift = sf::Vector2f(trajectory.y, -trajectory.x);
}

void PoisonDot::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	aliveTime += deltaTime;

	sprite.setScale(scale * (float)windowDimensions.x / 1920.0f, scale * windowDimensions.y / 1080.0f); //make scale a variable
	//sf::Vector2f currentTarget = target - (targetDrift * (1.f-(aliveTime*speed*1.7f/Math::Distance(target - spawnPosition,windowDimensions))));
	sf::Vector2f currentTarget = target - (targetDrift * 1.6f * cos(aliveTime * speed * 2.5f / Math::Distance(target - spawnPosition, windowDimensions)));

	direction = Math::normalizeVector(currentTarget - spawnPosition);

	sf::Vector2f movement = Math::windowNormalizeVector(Math::normalizeVector(direction) * speed * deltaTime, windowDimensions);
	cameraService.MoveSprite(sprite, movement);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());
	loopAnimation.Update(sprite, deltaTime);
}

sf::Sprite& PoisonDot::getSprite(void)
{
	return sprite;
}
