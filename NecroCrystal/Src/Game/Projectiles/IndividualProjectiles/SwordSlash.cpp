#include "SwordSlash.h"
#include "../../Utilities/Math.h"

SwordSlash::SwordSlash() :
	lifeSpan(960),liveTimer(0),
	loopAnimation(960.f/5.f, 5, 8, 16),descendingSpeed(0.09f)
{
	speed = 0.625f; //vitesse vers le bas
	faction = 2;
	scale = 4.f;
	damage = 17;
}

void SwordSlash::Load(const sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellDirection, sf::Vector2i& windowDimensions,bool flipped)
{
	sprite.setTexture(texture);
	loopAnimation.SetTextureRect(sprite);
	if (flipped)
		loopAnimation.Flip();
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

void SwordSlash::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	liveTimer += deltaTime;

	sprite.setScale(scale * (float)windowDimensions.x / 1920.0f, scale * windowDimensions.y / 1080.0f); //make scale a variable
	sf::Vector2f movement  = Math::windowNormalizeVector(direction * speed  * deltaTime, windowDimensions)
		+ Math::windowNormalizeVector(sf::Vector2f(0,descendingSpeed*deltaTime),windowDimensions);
	cameraService.MoveSprite(sprite, movement);

	hitbox.setScale(sprite.getScale());
	hitbox.setPosition(sprite.getGlobalBounds().getPosition());

	loopAnimation.Update(sprite, deltaTime);
}

sf::Sprite& SwordSlash::getSprite(void)
{
	return sprite;
}

bool SwordSlash::ShouldBeDestroyed(void) const
{
	return liveTimer>=lifeSpan;
}
