#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy/FireMage.h"
#include "../Utilities/CameraService.h"
#include "Character.h"

class Necromancer : public Character
{
protected:

public:
	Necromancer();
	~Necromancer();

	void Load(sf::Vector2i& windowDimensions);       //called once per App Start
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime);     //called once per frame

	sf::Sprite& getSprite(void) const;
};

