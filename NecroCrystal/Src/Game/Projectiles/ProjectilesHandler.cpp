#include "ProjectilesHandler.h"
#include<iostream>
#include "DarkProjectile.h"
#include "FireBall.h"
#include "../Characters/Necromancer.h"
#include "../Utilities/Math.h"

ProjectilesHandler::ProjectilesHandler() : 
    projectilesTextures(nullptr),textureNumber(2)
{
}

void ProjectilesHandler::Load()
{
    projectilesTextures = new sf::Texture[2];

    if (projectilesTextures[0].loadFromFile("Assets/Projectiles/darkProjectile.png"))
    {
        std::cout << "darkProjectile image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "darkProjectile image failed to load" << std::endl;
    }

    if (projectilesTextures[1].loadFromFile("Assets/Projectiles/fireball.png"))
    {
        std::cout << "fireProjectile image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "fireProjectile image failed to load" << std::endl;
    }

}

bool ProjectilesHandler::Update(std::vector<Character*>& characters, double deltaTime, sf::Vector2f& mousePosition, CameraService& cameraService, sf::Vector2i& windowDimensions,Map& map)
{
    for (auto& character : characters) //boucle qui rajoute les nouveaux projectiles
    {
        Projectile* projectile = character->LaunchProjectile(deltaTime,projectilesTextures, windowDimensions,mousePosition,characters);
        if (projectile != nullptr)
        {
            projectiles.push_back(projectile);
        }
    }

    bool isNecroDead = false;
    for (auto it = std::begin(projectiles); it!=std::end(projectiles); it++) //boucle qui update les charactères (les move + check position)
    {
        (*it)->Update(cameraService, windowDimensions, deltaTime);

        if (this->ProjectileCollisionChecker(*it, characters, map,isNecroDead))
        {
            delete(*it);
            projectiles.erase(it);
            it--;
            if (isNecroDead)
                return(isNecroDead);
        }
    }
    return(isNecroDead);
}

bool ProjectilesHandler::ProjectileCollisionChecker(Projectile* projectile,std::vector<Character*>& characters, Map& map, bool& isNecroDead)
{
    for (auto itChar = std::begin(characters); itChar != std::end(characters); itChar++)
    {
        if (projectile->getHitbox()->getGlobalBounds().intersects((*itChar)->getHitbox()->getGlobalBounds())
            && projectile->getFaction() != (*itChar)->getFaction())
        {
            if ((*itChar)->SetHealth((*itChar)->GetHealth() - projectile->getDamage()))
            {
                if (itChar == std::begin(characters))//check if it's the necromancer that died
                {
                    isNecroDead = true;
                    return(true);
                }
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

void ProjectilesHandler::Draw(sf::RenderWindow* window,bool drawHitbox) const
{
	for (auto& projectile : projectiles)
	{
		projectile->Draw(window,drawHitbox);
	}
}
