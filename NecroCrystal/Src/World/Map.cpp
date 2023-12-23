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
        


        tiles = new Tile[mapData.tilesNumber];

        for (size_t y = 0; y < totalTilesY; y++)
        {
            for (size_t x = 0; x < totalTilesX; x++)
            {
                int i = y * totalTilesX + x;
                tiles[i].id = i;
                tiles[i].position=sf::Vector2i(x * mapData.tileWidth, y * mapData.tileHeight);
            }
        }
        
    }
    else
    {
        std::cout << "NecroDungeon tileSheet texture failed to load" << std::endl;
    }

    mapSprites = new sf::Sprite*[mapData.mapHeight];
    for (size_t y = 0; y < mapData.mapHeight; y++)
    {
        mapSprites[y] = new sf::Sprite[mapData.mapWidth];
        for (size_t x = 0; x < mapData.mapWidth; x++)
        {
            int i = x + y * mapData.mapWidth;
            int tileIndex = mapData.tiles[y][x];
            mapSprites[y][x].setTexture(tileSheetTexture);
            mapSprites[y][x].setTextureRect(sf::IntRect(
                tiles[tileIndex].position.x,
                tiles[tileIndex].position.y,
                mapData.tileWidth,
                mapData.tileHeight
            ));
            mapSprites[y][x].setPosition(sf::Vector2f(x * mapData.tileWidth * (int)mapData.scaleX, y * mapData.tileHeight * (int)mapData.scaleY));
            mapSprites[y][x].setScale(mapData.scaleX, mapData.scaleY);
        }
    }

}

void Map::Update(float deltaTime, CameraService& cameraService)
{
    for (size_t y = 0; y < mapData.mapHeight; y++)
    {
        for (size_t x = 0; x < mapData.mapWidth; x++)
        {
            sf::Vector2f movement = sf::Vector2f(0,0);
            cameraService.MoveSprite(mapSprites[y][x], movement);
        }
    }
}

void Map::Draw(sf::RenderWindow& window)
{
    for (size_t y = 0; y < mapData.mapHeight; y++)
    {
        for (size_t x = 0; x < mapData.mapWidth; x++)
        {
            window.draw(mapSprites[y][x]);
        }
    }
}