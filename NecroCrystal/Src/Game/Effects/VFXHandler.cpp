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

	//SkeletonProjectile characteristics
	vFXsData.at(0).maxTimer=-1;
	vFXsData.at(0).followTarget=true;
	vFXsData.at(0).endOnTimer=false;
	vFXsData.at(0).speed=1.1f;
	vFXsData.at(0).refreshTimer=150;
	vFXsData.at(0).frameNumber=4;
	vFXsData.at(0).xFrameSize=16;
	vFXsData.at(0).yFrameSize=16;
	vFXsData.at(0).type=0;
}

void VFXHandler::SpawnVFX(sf::Vector2i& windowDimensions, sf::Vector2f position, sf::Vector2f target, int type)
{
	vFXs.push_back(VFX(vFXsData.at(type)));
	vFXs.back().Load(windowDimensions, position, target, textures[0]);
}

void VFXHandler::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
	for (auto& vFX : vFXs)
	{
		vFX.Update(cameraService, windowDimensions, deltaTime);
	}
}

void VFXHandler::DeleteExpiredVFX()
{
	std::erase_if(vFXs, [&](VFX& vFX) {return vFX.ShouldBeDeleted(); });
}

void VFXHandler::DrawVFX(sf::RenderWindow* window) const
{
	for (auto& vFX : vFXs)
	{
		vFX.Draw(window);
	}
}
