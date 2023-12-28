#include "ProjectilesHandler.h"
#include<iostream>
#include "DarkProjectile.h"
#include "../Characters/Necromancer.h"
#include "../Utilities/Math.h"

ProjectilesHandler::ProjectilesHandler() : timer(0),darkProjectileCastSpeed(400)
{
}

void ProjectilesHandler::Load()
{

    if (darkProjectileTexture.loadFromFile("Assets/Projectiles/darkProjectile.png"))
    {
        std::cout << "darkProjectile image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "darkProjectile image failed to load" << std::endl;
    }
}

void ProjectilesHandler::Update(std::vector<Character*>& characters, double deltaTime, sf::Vector2f& mousePosition, CameraService& cameraService, sf::Vector2i& windowDimensions,Map& map)
{
    timer += deltaTime;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && timer > darkProjectileCastSpeed) //darkSpell Creator
    {
        timer = 0;

        Projectile* darkProjectile = new DarkProjectile();
        sf::Vector2f spellPosition = ((Necromancer*) characters[0])->getSprite().getPosition() + 2.0f*
            sf::Vector2f(48 * (float)windowDimensions.x / 1920.0f, 6 * (float)windowDimensions.y / 1080.0f);
        darkProjectile->Load(darkProjectileTexture, spellPosition, mousePosition,windowDimensions);
        projectiles.push_back(darkProjectile);
    }


    for (auto it = std::begin(projectiles); it!=std::end(projectiles); it++) 
    {
        (*it)->Update(cameraService, windowDimensions, deltaTime);

        if (ProjectilesHandler::ProjectileCollisionChecker(*it, characters, map))
        {
            delete(*it);
            projectiles.erase(it);
            it--;
        }
    }
}

bool ProjectilesHandler::ProjectileCollisionChecker(Projectile* projectile,std::vector<Character*>& characters, Map& map)
{
    for (auto itChar = std::begin(characters); itChar != std::end(characters); itChar++)
    {
        if (projectile->getHitbox()->getGlobalBounds().intersects((*itChar)->getHitbox()->getGlobalBounds())
            && projectile->getFaction() != (*itChar)->getFaction())
        {
            if ((*itChar)->SetHealth((*itChar)->GetHealth() - 10))
            {
                delete(*itChar);
                characters.erase(itChar);
                itChar--;
            }
            return(true);
        }
    }

    if (map.ColideWithWall(projectile->getHitbox()))
    {
        return true;
    }
    return false;
}

void ProjectilesHandler::Draw(sf::RenderWindow* window) const
{
	for (auto& projectile : projectiles)
	{
		projectile->Draw(window);
	}
}
