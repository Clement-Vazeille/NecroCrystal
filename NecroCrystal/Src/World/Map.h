#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "MapData.h"
#include "../Utilities/CameraService.h"

class Map
{
private:
	sf::Texture tileSheetTexture;

	Tile* tiles;

	int totalTilesX;
	int totalTilesY;  //data about the tileeSheet

	MapData mapData;


	

	sf::Sprite** mapSprites;
public:
	Map();
	~Map();

	void Load();
	void Update(float deltaTime, CameraService& cameraService);
	void Draw(sf::RenderWindow& window);
};

