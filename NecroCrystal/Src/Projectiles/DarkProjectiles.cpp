#include "DarkProjectiles.h"
#include <iostream>
#include "../Utilities/Math.h"

DarkProjectiles::DarkProjectiles() :
    castSpeed(400),timer(0)
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

void DarkProjectiles::Update(Necromancer& necromancer,FireMage& fireMage,double deltaTime, sf::Vector2f& mousePosition, CameraService& cameraService)
{
    timer += deltaTime;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)&&timer>castSpeed)
    {
        timer = 0;

        DarkProjectile darkProjectile;
        sf::Vector2f spellPosition = necromancer.getSprite().getPosition() + sf::Vector2f(48, 6) * 2.0f;
        darkProjectile.Load(texture,spellPosition, mousePosition);
        projectiles.push_back(darkProjectile);
    }


    for (int i = projectiles.size()-1; i >=0; i--)
    {
        projectiles[i].Update(deltaTime,cameraService);
        
        
        if (fireMage.health > 0)
        {
            if (Math::SpriteCollision(projectiles[i].sprite, fireMage.sprite))
            {
                projectiles.erase(projectiles.begin() + i); //the code would be more optimised with a list instead of a vector 
                //but as the number of projectiles is unlikely to become higher then 10 the optimisation won't be noticeable

                fireMage.SetHealth(fireMage.health - 10);
                //std::cout << "Fire Mage Health: " <<fireMage.health<< std::endl;  
            }
        }
        
    }
}

void DarkProjectiles::Draw(sf::RenderWindow* window)
{

    for (size_t i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].Draw(window);
    }
}
