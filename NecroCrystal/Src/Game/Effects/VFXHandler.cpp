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

	if (textures.at(3).loadFromFile("Assets/FX/laserFx.png"))
		std::cout << "laser FX texture SpriteSheet loaded successfully" << std::endl;
	else
		std::cout << "failed to load laser FX texture" << std::endl;

	if (textures.at(4).loadFromFile("Assets/FX/PoisonFlaqueFx.png"))
		std::cout << "Poison Flaque FX texture SpriteSheet loaded successfully" << std::endl;
	else
		std::cout << "failed to load Poison Flauqe FX texture" << std::endl;

	if (textures.at(5).loadFromFile("Assets/FX/PoisonFlaqueSpawnFx.png"))
		std::cout << "Poison Flaque Spawn FX texture SpriteSheet loaded successfully" << std::endl;
	else
		std::cout << "failed to load Poison Flaque Spawn FX texture" << std::endl;

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
	vFXsData.at(2).scale = 10;
	vFXsData.at(2).type = 2;

	//laser VFX characteristics
	vFXsData.at(3).maxTimer = 1000;
	vFXsData.at(3).followTarget = true;
	vFXsData.at(3).endOnTimer = false;
	vFXsData.at(3).speed =0.8f;
	vFXsData.at(3).frameNumber = 3;
	vFXsData.at(3).refreshTimer = vFXsData.at(3).maxTimer / vFXsData.at(3).frameNumber;
	vFXsData.at(3).xFrameSize = 256;
	vFXsData.at(3).yFrameSize = 16;
	vFXsData.at(3).scale = 7;
	vFXsData.at(3).type = 3;

	//PoisonFlaque VFX characteristics
	vFXsData.at(4).maxTimer = 14000;
	vFXsData.at(4).followTarget = false;
	vFXsData.at(4).endOnTimer = true;
	vFXsData.at(4).speed = 0.f;
	vFXsData.at(4).frameNumber = 6;
	vFXsData.at(4).refreshTimer = vFXsData.at(4).maxTimer / vFXsData.at(4).frameNumber * 0.03f;
	vFXsData.at(4).xFrameSize = 32;
	vFXsData.at(4).yFrameSize = 128;
	vFXsData.at(4).scale = 4;
	vFXsData.at(4).type = 4;

	//PoisonFlaque Spawn VFX characteristics
	vFXsData.at(5).maxTimer = 1000;
	vFXsData.at(5).followTarget = false;
	vFXsData.at(5).endOnTimer = true;
	vFXsData.at(5).speed = 0.f;
	vFXsData.at(5).frameNumber = 4;
	vFXsData.at(5).refreshTimer = vFXsData.at(5).maxTimer / vFXsData.at(5).frameNumber;
	vFXsData.at(5).xFrameSize = 32;
	vFXsData.at(5).yFrameSize = 128;
	vFXsData.at(5).scale = 4;
	vFXsData.at(5).type = 5;
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
