#include "ProjectilesHandler.h"
#include<iostream>
#include "IndividualProjectiles/DarkProjectile.h"
#include "IndividualProjectiles/FireBall.h"
#include "../Characters/Necromancer.h"
#include "../Utilities/Math.h"

ProjectilesHandler::ProjectilesHandler()
{
}

ProjectilesHandler::~ProjectilesHandler()
{
    
    for (auto& projectile : projectiles)
    {
        delete projectile;
    }

    //if (projectilesTextures != nullptr)
    //    delete projectilesTextures;
    //TODO: make that delete work
}

void ProjectilesHandler::Load()
{
    projectilesTextures.Load();
}

bool ProjectilesHandler::Update(std::vector<Character*>& characters, double deltaTime, sf::Vector2f& mousePosition, CameraService& cameraService, 
    sf::Vector2i& windowDimensions,Map& map, SkeletonHandler& skeletonHandler, VFXHandler& vFXHandler)
{
    for (auto& character : characters) //boucle qui rajoute les nouveaux projectiles
    {
        Projectile* projectile = character->LaunchProjectile(deltaTime,projectilesTextures, windowDimensions,mousePosition,characters,vFXHandler);
        if (projectile != nullptr)
        {
            projectiles.push_back(projectile);
        }
    }

    bool isNecroDead = false;
    for (auto it = std::begin(projectiles); it!=std::end(projectiles); it++) //boucle qui check les collisions projectiles
    {
        (*it)->Update(cameraService, windowDimensions, deltaTime);

        if (this->ProjectileCollisionChecker(*it, characters, map,isNecroDead,windowDimensions,skeletonHandler,vFXHandler)//activate if projectile hit
            ||(*it)->ShouldBeDestroyed()) 
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

bool ProjectilesHandler::ProjectileCollisionChecker(Projectile* projectile,std::vector<Character*>& characters, Map& map, 
    bool& isNecroDead, sf::Vector2i& windowDimensions, SkeletonHandler& skeletonHandler,VFXHandler& vFXHandler)
{
    for (auto itChar = std::begin(characters); itChar != std::end(characters); itChar++)
    {
        if (projectile->getHitbox()->getGlobalBounds().intersects((*itChar)->getHitbox()->getGlobalBounds())
            && projectile->getFaction() != (*itChar)->getFaction() && (*itChar)->getFaction() != -1)
        {
            (*itChar)->TakeDamage(projectile->getDamage());
            if((*itChar)->getFaction()!=1)
                skeletonHandler.SkeletonAttack((*itChar),vFXHandler,windowDimensions);
            if ((*itChar)->TakeDamage(0)) //activate if character is dead
            {
                if (itChar == std::begin(characters))//check if it's the necromancer that died
                {
                    isNecroDead = true;
                    return(true);
                }
                skeletonHandler.SpawnSkeleton(windowDimensions, (*itChar)->getSprite().getPosition());
                delete(*itChar);
                characters.erase(itChar);
                itChar--;
            }
            return(true);
        }
    }

    if (map.ColideWithWall(projectile->getHitbox()) && projectile->IsWallDestroyable())
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
