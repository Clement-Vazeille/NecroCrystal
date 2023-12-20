#include "Map.h"
#include <iostream>

Map::Map():
    tileHeight(16),tileWidth(16),
    totalTilesX(0),totalTilesY(0)
{
}

Map::~Map()
{
}

void Map::Load()
{
    if (tileSheetTexture.loadFromFile("Assets/World/NecroDungeon/TileSheet.png"))
    {
        totalTilesX = tileSheetTexture.getSize().x / tileWidth;
        totalTilesY= tileSheetTexture.getSize().y / tileHeight;
        std::cout << totalTilesX << std::endl;
        std::cout << totalTilesY << std::endl;

        std::cout << "NecroDungeon tileSheet texture loaded successfully" << std::endl;
        sprite.setTexture(tileSheetTexture);
        sprite.setTextureRect(sf::IntRect(32, 32, tileWidth, tileHeight));
        sprite.setScale(5.0f,5.0f);
        sprite.setPosition(sf::Vector2f(100, 100));
    }
    else
    {
        std::cout << "NecroDungeon tileSheet texture failed to load" << std::endl;
    }
}

void Map::Update(float deltaTime)
{
}

void Map::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}