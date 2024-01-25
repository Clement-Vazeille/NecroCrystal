#include "VFX.h"

#include "../Utilities/Math.h"
VFX::VFX(int maxTimer, bool followTarget, bool endOnTimer) :
	animation(0, 0, 0, 0), scale(2),
	followTarget(followTarget), endOnTimer(endOnTimer),
	timer(0), maxTimer(maxTimer)
{
}

void VFX::Load(sf::Vector2i& windowDimensions, sf::Vector2f position, sf::Vector2f givenTarget,sf::Texture& texture)
{
	sprite.setTexture(texture);
	animation.SetTextureRect(sprite);
	sprite.scale(sf::Vector2f(scale * ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
	sprite.setPosition(sf::Vector2f(position.x * (double)windowDimensions.x / 1920.0, position.y * (double)windowDimensions.y / 1080.0));
	target = givenTarget; 
}

void VFX::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
}

void VFX::Draw(sf::RenderWindow* window) const
{
	window->draw(sprite);
}

bool VFX::ShouldBeDeleted(void) const
{
	float epsilonDistance = 3.f;
	if(Math::Distance(target - sprite.getPosition()) < epsilonDistance && followTarget)
		return true;
	if (timer >= maxTimer && endOnTimer)
		return true;
	return false;
}
