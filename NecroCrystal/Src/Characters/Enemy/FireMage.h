#pragma once
#include <SFML/Graphics.hpp>
#include "../../Utilities/CameraService.h"
#include "../../Utilities/LoopAnimation.h"
#include "Enemy.h"
#include "../../World//Map.h"
class FireMage : public Enemy
{
protected:
	sf::Font font;
	sf::Text healthText;
	float heathBarDistance;
	LoopAnimation loopAnimation;

public:
	FireMage();
	~FireMage();

	void Load(sf::Vector2i& windowDimensions,sf::Vector2f position);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime,Map& map);

	sf::Sprite& getSprite(void) const;
};

