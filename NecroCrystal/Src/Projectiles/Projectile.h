#pragma once
#include <SFML/Graphics.hpp>
#include "../Utilities/CameraService.h"

class Projectile
{
protected:
	sf::Vector2f target;
	sf::Vector2f direction;
	float speed;
	sf::Sprite sprite; //could become an array
	float castSpeed;
	int faction;
public:
	Projectile();
	virtual void Load(sf::Texture& texture, const sf::Vector2f& initalPosition, sf::Vector2f& spellTarget);
	virtual void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime) = 0; //rajouter l'entity list
	void Draw(sf::RenderWindow* window) const;
	float getCastSpeed(void) const;
};

