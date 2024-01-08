#include "LoopAnimation.h"

LoopAnimation::LoopAnimation(float refreshTimer, int frameNumber, int xFrameSize, int yFrameSize) : 
	refreshTimer(refreshTimer), frameNumber(frameNumber), 
	xFrameSize(xFrameSize),yFrameSize(yFrameSize),
	timer(0),actualFrame(0),flipped(false)
{
}

void LoopAnimation::Initialize(sf::Sprite& sprite)
{

	if(!flipped)
		sprite.setTextureRect(sf::IntRect(xFrameSize * actualFrame, 0, xFrameSize, yFrameSize));
	if(flipped)
		sprite.setTextureRect(sf::IntRect(xFrameSize * (actualFrame+1), 0, -xFrameSize, yFrameSize));
	actualFrame = (actualFrame + 1) % frameNumber;
}

void LoopAnimation::Update(sf::Sprite& sprite,float deltaTime)
{
	timer += deltaTime;
	if (timer >= refreshTimer)
	{
		timer = 0; //on aurait pu faire timer-=refreshTimer pour avoir une moyenne = refreshTimer et pas un peu supérieur
		if (!flipped)
			sprite.setTextureRect(sf::IntRect(xFrameSize * actualFrame, 0, xFrameSize, yFrameSize));
		if (flipped)
			sprite.setTextureRect(sf::IntRect(xFrameSize * (actualFrame + 1), 0, -xFrameSize, yFrameSize));
		actualFrame = (actualFrame+1) % frameNumber;
	}
}

void LoopAnimation::Reset(sf::Sprite& sprite)
{
	actualFrame = 0;
	timer = refreshTimer-1; //after a reset the animation should switch directly
	if (!flipped)
		sprite.setTextureRect(sf::IntRect(xFrameSize * actualFrame, 0, xFrameSize, yFrameSize));
	if (flipped)
		sprite.setTextureRect(sf::IntRect(xFrameSize * (actualFrame + 1), 0, -xFrameSize, yFrameSize));
}

void LoopAnimation::Flip(void)
{
	flipped = !flipped;
}
