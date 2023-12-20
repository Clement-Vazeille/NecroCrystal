#pragma once
#include <SFML/Graphics.hpp>

class Map
{
private:
	sf::Texture tileSheetTexture;
	sf::Sprite sprite;

	int tileWidth;
	int tileHeight;

	int totalTilesX;
	int totalTilesY;
public:
	Map();
	~Map();

	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

