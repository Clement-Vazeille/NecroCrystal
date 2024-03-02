#include "Animation.h"
#include <iostream>

Animation::Animation(float refreshTimer, int frameNumber, int xFrameSize, int yFrameSize) :
	refreshTimer(refreshTimer), frameNumber(frameNumber),
	xFrameSize(xFrameSize), yFrameSize(yFrameSize),
	xOffset(0),yOffset(0),
	timer(0), actualFrame(0), flipped(false)
{
}

Animation::Animation(float refreshTimer, int frameNumber, int xFrameSize, int yFrameSize, int xOffset,int yOffset) :
	refreshTimer(refreshTimer), frameNumber(frameNumber),
	xFrameSize(xFrameSize), yFrameSize(yFrameSize),
	xOffset(xOffset),yOffset(yOffset),
	timer(0), actualFrame(0), flipped(false)
{
}

void Animation::SetTextureRect(sf::Sprite& sprite)
{
	if(!flipped)
		sprite.setTextureRect(sf::IntRect(xFrameSize * (actualFrame+xOffset), yOffset*yFrameSize, xFrameSize, yFrameSize));
	if(flipped)
		sprite.setTextureRect(sf::IntRect(xFrameSize * (actualFrame+xOffset+1), yOffset * yFrameSize, -xFrameSize, yFrameSize));
}

void Animation::Update(sf::Sprite& sprite,float deltaTime)
{
	timer += deltaTime;
	if (timer >= refreshTimer)
	{
		timer = 0; //on aurait pu faire timer-=refreshTimer pour avoir une moyenne = refreshTimer et pas un peu supérieur
		actualFrame = (actualFrame + 1) % frameNumber;
	}
	this->SetTextureRect(sprite);
}

void Animation::Reset(sf::Sprite& sprite)
{
	actualFrame = 0;
	timer = 0; //after a reset the animation should switch directly
	this->SetTextureRect(sprite);
}

void Animation::Flip(void)
{
	flipped = !flipped;
}

void Animation::MoveOffsets(int xChange, int yChange)
{
	xOffset += xChange;
	yOffset += yChange;
}
