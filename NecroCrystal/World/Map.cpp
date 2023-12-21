#include "Map.h"
#include <iostream>

Map::Map():
    tileHeight(16),tileWidth(16),
    totalTilesX(0),totalTilesY(0),totalTiles(0)
{
}

Map::~Map()
{
}

void Map::Load()
{
    if (tileSheetTexture.loadFromFile("Assets/World/NecroDungeon/TileSheet.png"))
    {
        std::cout << "NecroDungeon tileSheet texture loaded successfully" << std::endl;
        
        totalTilesX = tileSheetTexture.getSize().x / tileWidth;
        totalTilesY= tileSheetTexture.getSize().y / tileHeight;
        std::cout << totalTilesX << std::endl;
        std::cout << totalTilesY << std::endl;

        totalTiles = totalTilesX * totalTilesY;

        tiles = new Tile[totalTiles];

        for (size_t y = 0; y < totalTilesY; y++)
        {
            for (size_t x = 0; x < totalTilesX; x++)
            {
                int i = y * totalTilesX + x;
                tiles[i].id = i;
                tiles[i].texture = &tileSheetTexture;
                tiles[i].position=sf::Vector2i(x * tileWidth, y * tileHeight);
                //tiles[i].sprite.setScale(4.0f, 4.0f);
                //tiles[i].sprite.setPosition(sf::Vector2f(100 + x * tileWidth * 4, 100 + y * tileWidth * 4));
            }
        }
        
    }
    else
    {
        std::cout << "NecroDungeon tileSheet texture failed to load" << std::endl;
    }

    for (size_t y = 0; y < 2; y++)
    {
        for (size_t x = 0; x < 3; x++)
        {
            int i = x + y * 3;
            int tileIndex = mapTilesID[i];
            mapSprites[i].setTexture(*tiles[tileIndex].texture);
            mapSprites[i].setTextureRect(sf::IntRect(
                tiles[tileIndex].position.x,
                tiles[tileIndex].position.y,
                tileWidth,
                tileHeight
            ));
            mapSprites[i].setPosition(sf::Vector2f(x * 16*4, y * 16*4));
            mapSprites[i].setScale(4.0f, 4.0f);
        }
    }

}

void Map::Update(float deltaTime)
{

}

void Map::Draw(sf::RenderWindow& window)
{
    for (size_t i = 0; i < 6; i++)
    {
        window.draw(mapSprites[i]);
    }
    
}