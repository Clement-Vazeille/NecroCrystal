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


	static const int mapSize = 6;

	int mapTilesID[mapSize] = { //TODO transformer ça en une matrice
		2,0,1,
		2,1,0
	};
	sf::Sprite mapSprites[mapSize];
public:
	Map();
	~Map();

	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

