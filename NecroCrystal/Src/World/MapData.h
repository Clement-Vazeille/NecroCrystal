#pragma once
#include<string>
#include <SFML/Graphics.hpp>

struct MapData
{
	std::string tileSheet = "";
	std::string name = "";

	int tileWidth = 0;
	int tileHeight = 0;
	
	float scaleX = 0;
	float scaleY = 0;

	int mapWidth = 0;//limitation: on ne peut faire que des maps rectangulaires
	int mapHeight = 0;

	int tilesNumber = 0;
	int** tiles = nullptr;

	int hitboxNumber = 0;
	sf::Vector2f* wallHitboxPositions = nullptr; //hitboxes from every wall of the map
	sf::Vector2f* wallHitboxSizes = nullptr;
};