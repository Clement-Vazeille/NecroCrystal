#include "VFX.h"

#include <iostream>
#include "../Utilities/Math.h"
VFX::VFX(VFXdata& vFXdata) :
	animation(vFXdata.refreshTimer, vFXdata.frameNumber, vFXdata.xFrameSize, vFXdata.yFrameSize), scale(2),
	followTarget(vFXdata.followTarget), endOnTimer(vFXdata.endOnTimer),
	timer(0), maxTimer(vFXdata.maxTimer),speed(vFXdata.speed)
{
}

void VFX::Load(sf::Vector2i& windowDimensions, sf::Vector2f position, sf::Vector2f givenTarget,sf::Texture& texture)
{
	sprite.setTexture(texture);
	animation.SetTextureRect(sprite);
	sprite.scale(sf::Vector2f(scale * ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
	sprite.setPosition(position);
	target = givenTarget; 
	
	if (target.x < position.x && followTarget)
		animation.Flip();
}

void VFX::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	timer += deltaTime;
	sprite.setScale(sf::Vector2f(scale * ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));
	animation.Update(sprite, deltaTime);

	if (followTarget)
	{
		cameraService.UpdateVector(target);
		sf::Vector2f movement = Math::normalizeVector(target - sprite.getPosition()) * speed * deltaTime;
		cameraService.MoveSprite(sprite, movement); //goes from 900 to 0 but work normaly after
	}
}

void VFX::Draw(sf::RenderWindow* window) const
{
	window->draw(sprite);
}

bool VFX::ShouldBeDeleted(sf::Vector2i& windowDimensions) const
{
	float epsilonDistance = 2.f;
	if(Math::Distance(target - sprite.getPosition(),windowDimensions) < epsilonDistance && followTarget)
		return true;
	if (timer >= maxTimer && endOnTimer)
		return true;
	return false;
}
