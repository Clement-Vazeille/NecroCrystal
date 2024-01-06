#pragma once
#include "../Character.h"
#include "../../Utilities/LoopAnimation.h"

class Enemy : public Character
{
protected: 
	LoopAnimation healthAnimation;
	sf::Texture healthTexture;
	double removedNotCountedHealth;
public :
	Enemy();
	void LoadHealthBar(sf::Vector2i& windowDimensions, sf::Vector2f position);
	bool SetHealth(int hp);
};

