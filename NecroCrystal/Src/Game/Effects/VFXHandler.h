#pragma once

#include <array>
#include <vector>

#include "VFX.h"

class VFXHandler
{
protected:
	std::array<sf::Texture,1> textures;
	std::vector<VFX> VFXs;

public:
	VFXHandler();

	void LoadTextures(void);
	void SpawnVFX(sf::Vector2i& windowDimensions, sf::Vector2f position, int id);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime);
	void DeleteExpiredVFX();
	void DrawVFX(sf::RenderWindow* window) const;
};

