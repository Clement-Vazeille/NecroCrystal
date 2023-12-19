#include "DarkProjectiles.h"
#include <iostream>
#include "../Utilities/Math.h"


DarkProjectiles::DarkProjectiles() :
    speed (0.5f),castSpeed(400),timer(0)
{
}

void DarkProjectiles::Load()
{
    if (texture.loadFromFile("Assets/Projectiles/darkProjectile.png"))
    {
        std::cout << "darkProjectile image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "darkProjectile image failed to load" << std::endl;
    }
}

void DarkProjectiles::Update(Necromancer& necromancer,FireMage& fireMage,double deltaTime)
{
    timer += deltaTime;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)&&timer>castSpeed)
    {
        timer = 0;

        DarkProjectile darkProjectile;
        darkProjectile.Load(texture);
        darkProjectile.sprite.setPosition(necromancer.sprite.getPosition() + sf::Vector2f(64, 20)*2.0f);
        projectiles.push_back(darkProjectile);
    }
    for (int i = projectiles.size()-1; i >=0; i--)
    {
        sf::Vector2f direction = fireMage.sprite.getPosition() +sf::Vector2f(20,20)*2.0f - projectiles[i].sprite.getPosition();
        projectiles[i].sprite.setPosition(projectiles[i].sprite.getPosition() + Math::normalizeVector(direction) *speed * (float)deltaTime);
        
        if (Math::SpriteCollision(projectiles[i].sprite, fireMage.sprite))
        {
            projectiles.erase(projectiles.begin() + i); //the code would be more optimised with a list instead of a vector 
            //but as the number of projectiles is unlikely to become higher then 10 the optimisation won't be noticeable

            fireMage.health -= 10;
            //std::cout << "Fire Mage Health: " <<fireMage.health<< std::endl;  
        }
    }
}

void DarkProjectiles::Draw(sf::RenderWindow& window)
{

    for (size_t i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].Draw(window);
    }
}
