#pragma once
#include "../Character.h"
#include "../../Utilities/LoopAnimation.h"

class Enemy : public Character
{
protected: 
	LoopAnimation healthAnimation;
	sf::Texture healthTexture;
	double removedNotCountedHealth;

	bool activated;
	float activatedDistance;

	const int serial; //for skeletons who can only hit an enemy once per dash
public :
	Enemy();
	void LoadHealthBar(sf::Vector2i& windowDimensions, sf::Vector2f position);
	bool SetHealth(int hp);

	const int GetSerial(void) const;
	static int enemyNumber;
};

//int Enemy::enemyNumber = 0;
