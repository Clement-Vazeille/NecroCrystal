#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "MapData.h"

class Map
{
private:
	sf::Texture tileSheetTexture;

	Tile* tiles;

	int totalTilesX;
	int totalTilesY;  //data about the tileeSheet

	MapData mapData;


	

	sf::Sprite* mapSprites;
public:
	Map();
	~Map();

	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

