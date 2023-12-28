#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy/FireMage.h"
#include "../Utilities/CameraService.h"
#include "Character.h"
#include "../World//Map.h"

class Necromancer : public Character
{
protected:

public:
	Necromancer();
	~Necromancer();

	void Load(sf::Vector2i& windowDimensions,sf::Vector2f position);       //called once per App Start
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map);     //called once per frame

	sf::Sprite& getSprite(void) const;
};

