#pragma once

#include <SFML/Graphics.hpp>
#include "../Utilities/CameraService.h"
#include "Projectile.h"
#include "../Utilities/Animation.h"


class SwordSlash : public Projectile
{
protected:
	Animation loopAnimation;
public:
	SwordSlash();

	void Load(sf::Texture& texture, const sf::Vector2f& initialPosition, sf::Vector2f& spellTarget, sf::Vector2i& windowDimensions);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime);
	sf::Sprite& getSprite(void);
};

