#include "ProjectilesHandler.h"
#include<iostream>

ProjectilesHandler::ProjectilesHandler() : timer(0)
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

void ProjectilesHandler::Update(std::vector<Character*>, double deltaTime, sf::Vector2f& mousePosition, CameraService& cameraService, sf::Vector2i& windowDimensions)
{
}

void ProjectilesHandler::Draw(sf::RenderWindow* window) const
{
	for (auto& projectile : projectiles)
	{
		projectile.Draw(window);
	}
}
