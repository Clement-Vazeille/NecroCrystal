#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
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

	sf::RectangleShape* wallHitbox;
public:
	Map();
	~Map();

	void Load(sf::Vector2i mapDimensions);
	void Update(float deltaTime, CameraService& cameraService, sf::Vector2i mapDimensions);
	void Draw(sf::RenderWindow* window);

	bool ColideWithWall(sf::RectangleShape* hitbox) const;

	MapData* getData(void);
};

