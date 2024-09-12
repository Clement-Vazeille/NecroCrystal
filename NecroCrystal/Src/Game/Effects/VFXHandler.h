#pragma once

#include <array>
#include <vector>

#include "VFX.h"

class VFXHandler
{
protected:
	std::array<sf::Texture,4> textures;
	std::array<VFXdata, 4> vFXsData;
	std::vector<VFX> vFXs;

public:
	VFXHandler();

	void LoadTextures(void);
	void SpawnVFX(sf::Vector2i& windowDimensions, sf::Vector2f position,sf::Vector2f target, int type);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime);
	void DeleteExpiredVFX(sf::Vector2i& windowDimensions);
	void DrawVFX(sf::RenderWindow* window) const;
};

