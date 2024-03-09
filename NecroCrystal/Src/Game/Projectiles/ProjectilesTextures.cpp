#include "ProjectilesTextures.h"
#include <iostream>

ProjectilesTextures::ProjectilesTextures()
{
}

void ProjectilesTextures::Load()
{
    if (darkProjectile.loadFromFile("Assets/Projectiles/darkProjectile.png"))
    {
        std::cout << "darkProjectile image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "darkProjectile image failed to load" << std::endl;
    }

    if (fireBall.loadFromFile("Assets/Projectiles/fireball.png"))
    {
        std::cout << "fireProjectile image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "fireProjectile image failed to load" << std::endl;
    }

    if (swordSlash.loadFromFile("Assets/Projectiles/meleMageProjectile.png"))
    {
        std::cout << "fireProjectile image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "fireProjectile image failed to load" << std::endl;
    }
}
