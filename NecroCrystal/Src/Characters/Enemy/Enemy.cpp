#include "Enemy.h"
#include <iostream>

Enemy::Enemy() :
	healthAnimation(0,12,64,32)
{
}

void Enemy::LoadHealthBar(sf::Vector2i& windowDimensions, sf::Vector2f position)
{
    if (healthTexture.loadFromFile("Assets/OtherMages/hpBarEnemy.png"))
    {
        std::cout << "HealthBar image loaded successfully" << std::endl;
        sprites[1].setTexture(healthTexture);

        healthAnimation.Initialize(sprites[1]);
        sprites[1].scale(sf::Vector2f(scale * (double)windowDimensions.x / 1920.0, scale * (double)windowDimensions.y / 1080.0));//multiplie la taille par scale (c'est 2)
        sprites[1].setPosition(sf::Vector2f(position.x * (double)windowDimensions.x / 1920.0, (position.y-50) * (double)windowDimensions.y / 1080.0));
    }
    else
    {
        std::cout << "FireMage image failed to load" << std::endl;
    }
}

bool Enemy::SetHealth(int hp)
{
	health = hp;
    healthAnimation.Update(sprites[1], 0);
	return(health <= 0);
}
