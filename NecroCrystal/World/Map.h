#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Map
{
private:
	sf::Texture tileSheetTexture;

	Tile* tiles;

	int tileWidth;
	int tileHeight;

	int totalTilesX;
	int totalTilesY;
	int totalTiles;

	int mapTilesID[6] = {
		2,0,1,
		2,1,0
	};
	sf::Sprite mapSprites[6];
public:
	Map();
	~Map();

	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

