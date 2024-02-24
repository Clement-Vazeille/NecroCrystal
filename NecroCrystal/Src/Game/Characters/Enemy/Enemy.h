#pragma once
#include "../Character.h"
#include "../../Utilities/Animation.h"

class Enemy : public Character
{
protected: 
	Animation healthAnimation;
	sf::Texture healthTexture;
	double removedNotCountedHealth;

	float healthBarScaleX;
	float healthBarScaleY;

	bool activated;
	float activatedDistance;

	const int serial; //for skeletons who can only hit an enemy once per dash
public :
	Enemy();
	void LoadHealthBar(sf::Vector2i& windowDimensions, sf::Vector2f position);
	
	bool TakeDamage(int hp);
	void Activate(void);

	const int GetSerial(void) const;
	static int enemyNumber;
};

//int Enemy::enemyNumber = 0;
