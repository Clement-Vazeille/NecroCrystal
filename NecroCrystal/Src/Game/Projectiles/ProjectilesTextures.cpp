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
    if (captainSlash.loadFromFile("Assets/Projectiles/CaptainSlash.png"))
    {
        std::cout << "CaptainSlash image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "CaptainSlash image failed to load" << std::endl;
    }
    if (poisonDot.loadFromFile("Assets/Projectiles/PoisonDot.png"))
    {
        std::cout << "PoisonDot image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "PoisonDot image failed to load" << std::endl;
    }
    if (laser.loadFromFile("Assets/Projectiles/laser.png"))
    {
        std::cout << "Laser image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "laser image failed to load" << std::endl;
    }
    if (poisonFlaque.loadFromFile("Assets/Projectiles/PoisonFlaque.png"))
    {
        std::cout << "Poison Flaque image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "Poison Flaque image failed to load" << std::endl;
    }
}
