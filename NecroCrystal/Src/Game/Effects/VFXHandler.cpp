#include "VFXHandler.h"
#include <iostream>

VFXHandler::VFXHandler()
{
}

void VFXHandler::LoadTextures(void)
{
	if (textures.at(0).loadFromFile("Assets/FX/SkeletonAttack.png"))
		std::cout << "Skeleton attack texture SpriteSheet loaded successfully" << std::endl;
	else
		std::cout << "failed to load Skeleton attack texture" << std::endl;

	if (textures.at(1).loadFromFile("Assets/FX/NecroZoneParticule.png"))
		std::cout << "NecroZoneParticule texture SpriteSheet loaded successfully" << std::endl;
	else
		std::cout << "failed to load NecrpZoneParticule texture" << std::endl;

	if (textures.at(2).loadFromFile("Assets/FX/explosionVFX.png"))
		std::cout << "explosion FX texture SpriteSheet loaded successfully" << std::endl;
	else
		std::cout << "failed to load explosion FX texture" << std::endl;

	//SkeletonProjectile characteristics
	vFXsData.at(0).maxTimer=-1;
	vFXsData.at(0).followTarget=true;
	vFXsData.at(0).endOnTimer=false;
	vFXsData.at(0).speed=1.1f;
	vFXsData.at(0).refreshTimer=150;
	vFXsData.at(0).frameNumber=4;
	vFXsData.at(0).xFrameSize=16;
	vFXsData.at(0).yFrameSize = 16;
	vFXsData.at(0).scale = 2;
	vFXsData.at(0).type=0;

	//NecroZoneParticules characteristics
	vFXsData.at(1).maxTimer = 1200;
	vFXsData.at(1).followTarget = false;
	vFXsData.at(1).endOnTimer = true;
	vFXsData.at(1).speed = 0;
	vFXsData.at(1).frameNumber = 6;
	vFXsData.at(1).refreshTimer = vFXsData.at(1).maxTimer/ vFXsData.at(1).frameNumber;
	vFXsData.at(1).xFrameSize = 16;
	vFXsData.at(1).yFrameSize = 16;
	vFXsData.at(1).scale = 2;
	vFXsData.at(1).type = 1;

	//explosion VFX characteristics
	vFXsData.at(2).maxTimer = 1600;
	vFXsData.at(2).followTarget = false;
	vFXsData.at(2).endOnTimer = true;
	vFXsData.at(2).speed = 0;
	vFXsData.at(2).frameNumber = 8;
	vFXsData.at(2).refreshTimer = vFXsData.at(2).maxTimer / vFXsData.at(2).frameNumber;
	vFXsData.at(2).xFrameSize = 32;
	vFXsData.at(2).yFrameSize = 32;
	vFXsData.at(2).scale = 6;
	vFXsData.at(2).type = 2;
}

void VFXHandler::SpawnVFX(sf::Vector2i& windowDimensions, sf::Vector2f position, sf::Vector2f target, int type)
{
	vFXs.push_back(VFX(vFXsData.at(type)));
	vFXs.back().Load(windowDimensions, position, target, textures[type]);
}

void VFXHandler::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	for (auto& vFX : vFXs)
	{
		vFX.Update(cameraService, windowDimensions, deltaTime);
	}
}

void VFXHandler::DeleteExpiredVFX(sf::Vector2i& windowDimensions)
{
	std::erase_if(vFXs, [&](VFX& vFX) {return vFX.ShouldBeDeleted(windowDimensions); });
}

void VFXHandler::DrawVFX(sf::RenderWindow* window) const
{
	for (auto& vFX : vFXs)
	{
		vFX.Draw(window);
	}
}
