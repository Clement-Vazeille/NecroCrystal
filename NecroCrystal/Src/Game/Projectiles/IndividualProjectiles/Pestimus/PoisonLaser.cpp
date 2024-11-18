#include "PoisonLaser.h"
#include "../../../Utilities/Math.h"

PoisonLaser::PoisonLaser() : 
	lifeSpan(200), liveTimer(0),
	loopAnimation(300.f / 3.f, 3, 256, 16)
{
	speed = 0.8f; 
	faction = 2;
	scale = 6.5f;
	damage = 5;
}

void PoisonLaser::Load(const sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellDirection, sf::Vector2i& windowDimensions)
{
	sprite.setTexture(texture);
	loopAnimation.SetTextureRect(sprite);
	hitbox.setSize(sprite.getGlobalBounds().getSize());
	sprite.setScale(sf::Vector2f(scale * (float)windowDimensions.x / 1920.0f, scale * (float)windowDimensions.y / 1080.0f));
	sprite.setPosition(initialPosition);

	direction = spellDirection;

	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(-1);
	hitbox.setFillColor(sf::Color::Transparent);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());
}

void PoisonLaser::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	liveTimer += deltaTime;

	sprite.setScale(scale * (float)windowDimensions.x / 1920.0f, scale * windowDimensions.y / 1080.0f); //make scale a variable
	sf::Vector2f movement = Math::windowNormalizeVector(sf::Vector2f(0, speed * deltaTime), windowDimensions);
	cameraService.MoveSprite(sprite, movement);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());

	loopAnimation.Update(sprite, deltaTime);
}

sf::Sprite& PoisonLaser::getSprite(void)
{
	return sprite;
}

bool PoisonLaser::ShouldBeDestroyed(void) const
{
	return liveTimer >= lifeSpan;
}
