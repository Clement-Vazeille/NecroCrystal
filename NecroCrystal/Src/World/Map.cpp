#include "Map.h"
#include <iostream>
#include "MapLoader.h"

Map::Map():
    totalTilesX(0),totalTilesY(0),
    tiles(nullptr),mapSprites(nullptr)
{
}

Map::~Map()
{
}

void Map::Load()
{
    MapLoader::Load("Assets/World/NecroDungeon/NecroDungeon.map", mapData);
    if (tileSheetTexture.loadFromFile(mapData.tileSheet))
    {
        std::cout << "NecroDungeon tileSheet texture loaded successfully" << std::endl;
        
        totalTilesX = tileSheetTexture.getSize().x / mapData.tileWidth;
        totalTilesY= tileSheetTexture.getSize().y / mapData.tileHeight;
        mapSprites = new sf::Sprite[mapData.tilesNumber];


        tiles = new Tile[mapData.tilesNumber];

        for (size_t y = 0; y < totalTilesY; y++)
        {
            for (size_t x = 0; x < totalTilesX; x++)
            {
                int i = y * totalTilesX + x;
                tiles[i].id = i;
                tiles[i].position=sf::Vector2i(x * mapData.tileWidth, y * mapData.tileHeight);
                //tiles[i].sprite.setScale(4.0f, 4.0f);
                //tiles[i].sprite.setPosition(sf::Vector2f(100 + x * tileWidth * 4, 100 + y * tileWidth * 4));
            }
        }
        
    }
    else
    {
        std::cout << "NecroDungeon tileSheet texture failed to load" << std::endl;
    }
    for (size_t y = 0; y < mapData.mapHeight; y++)
    {
        for (size_t x = 0; x < mapData.mapWidth; x++)
        {
            int i = x + y * mapData.mapWidth;
            int tileIndex = mapData.tiles[i];
            mapSprites[i].setTexture(tileSheetTexture);
            mapSprites[i].setTextureRect(sf::IntRect(
                tiles[tileIndex].position.x,
                tiles[tileIndex].position.y,
                mapData.tileWidth,
                mapData.tileHeight
            ));
            mapSprites[i].setPosition(sf::Vector2f(x * mapData.tileWidth*(int)mapData.scaleX, y * mapData.tileHeight * (int)mapData.scaleY));
            mapSprites[i].setScale(mapData.scaleX, mapData.scaleY);
        }
    }

}

void Map::Update(float deltaTime)
{

}

void Map::Draw(sf::RenderWindow& window)
{
    for (size_t i = 0; i < mapData.tilesNumber; i++)
    {
        window.draw(mapSprites[i]);
    }
    
}