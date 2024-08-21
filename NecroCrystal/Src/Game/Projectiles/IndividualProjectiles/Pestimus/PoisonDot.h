#pragma once

#include <SFML/Graphics.hpp>
#include "../../../Utilities/CameraService.h"
#include "../../Projectile.h"
#include "../../../Utilities/Animation.h"

class PoisonDot : public Projectile
{
protected:
	float aliveTime;

	sf::Vector2f targetDrift;
	sf::Vector2f spawnPosition;

	Animation loopAnimation;
public:
	PoisonDot();

	void InverseTrajectory(void);

	void Load(const sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellTarget, sf::Vector2i& windowDimensions);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime);
	sf::Sprite& getSprite(void);
};

