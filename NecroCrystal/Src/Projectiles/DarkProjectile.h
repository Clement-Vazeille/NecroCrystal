#pragma once
#include <SFML/Graphics.hpp>
#include "../Utilities/CameraService.h"

class DarkProjectile
{
private:
	sf::Vector2f target;
	sf::Vector2f direction;
	float speed;
public:
	sf::Sprite sprite;
	
public:
	DarkProjectile();

	void Load(sf::Texture& texture,const sf::Vector2f& initalPosition,sf::Vector2f& spellTarget);
	void Update(float deltaTime,CameraService& cameraService);
	void Draw(sf::RenderWindow& window);
};

