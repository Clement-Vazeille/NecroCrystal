#pragma once
#include <SFML/Graphics.hpp>


//Class used to handle a animation loop
//the texture file has to contains all animation frames left to right in a single line
class LoopAnimation
{
protected:
	float timer;
	float refreshTimer;

	int frameNumber;
	int actualFrame;

	int xFrameSize;
	int yFrameSize;

	bool flipped;
public:
	LoopAnimation(float refreshTimer,int frameNumber,int xFrameSize,int yFrameSize);

	void Initialize(sf::Sprite& sprite);
	void Update(sf::Sprite& sprite, float deltaTime);
	void Reset(sf::Sprite& sprite);
	void Flip(void);
};

