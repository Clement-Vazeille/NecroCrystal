#include "CaptainSlash.h"
#include "../../../Utilities/Math.h"

CaptainSlash::CaptainSlash() :
	lifeSpan(600), liveTimer(0),
	slashAnimation(200,3,32,32)
{
	speed = 0.2f;
	faction = 2;
	scale = 15.f;
	damage = 30;
}

void CaptainSlash::Load(const sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellTarget, sf::Vector2i& windowDimensions)
{
	this->Projectile::Load(texture, initialPosition, spellTarget, windowDimensions);
	slashAnimation.SetTextureRect(sprite);
	hitbox.setSize(sprite.getGlobalBounds().getSize() / scale);
}

void CaptainSlash::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
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

	slashAnimation.Update(sprite, deltaTime);
}

sf::Sprite& CaptainSlash::getSprite(void)
{
	return sprite;
}

bool CaptainSlash::ShouldBeDestroyed(void) const
{
	return liveTimer >= lifeSpan;
}
