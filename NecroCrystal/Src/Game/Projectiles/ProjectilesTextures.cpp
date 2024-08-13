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

    if (fireBall.loadFromFile("Assets/Projectiles/fireballAnimated.png"))
    {
        std::cout << "fireProjectile image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "fireProjectile image failed to load" << std::endl;
    }

    if (swordSlash.loadFromFile("Assets/Projectiles/meleMageProjectile.png"))
    {
        std::cout << "swordSlash image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "swordSlash image failed to load" << std::endl;
    }

    if (explosion.loadFromFile("Assets/Projectiles/explosion.png"))
    {
        std::cout << "explosion image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "explosion image failed to load" << std::endl;
    }
    if (hammer.loadFromFile("Assets/Projectiles/hammerThrow.png"))
    {
        std::cout << "hammer image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "hammer image failed to load" << std::endl;
    }
}
