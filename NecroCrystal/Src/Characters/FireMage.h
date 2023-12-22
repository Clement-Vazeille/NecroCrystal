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

public:
	int health;
	sf::Sprite sprite;
public:
	FireMage();

	void Load(int x, int y);
	void Update(CameraService& cameraService);
	void SetHealth(int hp);
	void Draw(sf::RenderWindow& window);
};

