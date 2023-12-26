#pragma once
#include <SFML/Graphics.hpp>
#include "../../Utilities/CameraService.h"
#include "Enemy.h"
class FireMage : public Enemy
{
protected:
	sf::Font font;
	sf::Text healthText;
	float heathBarDistance;

public:
	FireMage();
	~FireMage();

	void Load(sf::Vector2i& windowDimensions);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime);

	sf::Sprite& getSprite(void) const;
};

