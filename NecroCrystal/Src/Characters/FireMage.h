#pragma once
#include <SFML/Graphics.hpp>
#include "../Utilities/CameraService.h"
class FireMage
{
private:
	sf::Texture texture;
	int width;
	int height;
	int scale;
	sf::Font font;
	sf::Text healthText;
	float heathBarDistance;

public:
	int health;
	sf::Sprite sprite;
public:
	FireMage();

	void Load(sf::Vector2i& windowDimensions);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions);
	void SetHealth(int hp);
	void Draw(sf::RenderWindow* window);
};

