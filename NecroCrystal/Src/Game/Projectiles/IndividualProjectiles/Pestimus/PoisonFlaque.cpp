#include "PoisonFlaque.h"
#include "../../../Utilities/Math.h"

PoisonFlaque::PoisonFlaque() :
	lifeSpan(250), liveTimer(0),
	loopAnimation(250.f / 1.f, 1, 32, 128)
{
	speed = 0.f;
	faction = 2;
	scale = 4.f;
	damage = 4;
}

void PoisonFlaque::Load(const sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellTarget, sf::Vector2i& windowDimensions)
{
	sprite.setTexture(texture);
	loopAnimation.SetTextureRect(sprite);
	hitbox.setSize(sprite.getGlobalBounds().getSize());
	sprite.setScale(sf::Vector2f(scale * (float)windowDimensions.x / 1920.0f, scale * (float)windowDimensions.y / 1080.0f));
	sprite.setPosition(initialPosition);

	direction = spellTarget;

	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(-1);
	hitbox.setFillColor(sf::Color::Transparent);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());
}

void PoisonFlaque::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	liveTimer += deltaTime;

	sprite.setScale(scale * (float)windowDimensions.x / 1920.0f, scale * windowDimensions.y / 1080.0f); //make scale a variable
	sf::Vector2f movement = Math::windowNormalizeVector(sf::Vector2f(0, 0), windowDimensions);
	cameraService.MoveSprite(sprite, movement);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());

	loopAnimation.Update(sprite, deltaTime);
}

sf::Sprite& PoisonFlaque::getSprite(void)
{
	return sprite;
}

bool PoisonFlaque::ShouldBeDestroyed(void) const
{
	return liveTimer >= lifeSpan;
}
