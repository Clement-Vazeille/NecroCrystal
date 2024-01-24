#pragma once
#include <SFML/Graphics.hpp>


//Class used to handle a animation loop
//the texture file has to contains all animation frames left to right in a single line
class Animation
{
protected:
	float timer;
	float refreshTimer;

	int xOffset;
	int yOffset;
	int frameNumber;
	int actualFrame;

	int xFrameSize;
	int yFrameSize;

	bool flipped;
public:
	Animation(float refreshTimer,int frameNumber,int xFrameSize,int yFrameSize);
	Animation(float refreshTimer, int frameNumber, int xFrameSize, int yFrameSize,int xOffset,int yOffset);

	void Initialize(sf::Sprite& sprite); //set Sprite to current frame and do currentFrame ++
	void Update(sf::Sprite& sprite, float deltaTime);
	void Reset(sf::Sprite& sprite);
	void Flip(void);
	void MoveOffsets(int xChange, int yChange);
};

