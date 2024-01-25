#include "VFXHandler.h"

VFXHandler::VFXHandler()
{
}

void VFXHandler::LoadTextures(void)
{
}

void VFXHandler::SpawnVFX(sf::Vector2i& windowDimensions, sf::Vector2f position, int id)
{
}

void VFXHandler::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)
{
}

void VFXHandler::DeleteExpiredVFX()
{
}

void VFXHandler::DrawVFX(sf::RenderWindow* window) const
{
	for (auto& vFX : VFXs)
	{

	}
}
