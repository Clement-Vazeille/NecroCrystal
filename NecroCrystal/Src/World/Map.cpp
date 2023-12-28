#include "Map.h"
#include <iostream>
#include "MapLoader.h"

Map::Map():
    totalTilesX(0),totalTilesY(0),
    tiles(nullptr),mapSprites(nullptr),wallHitbox(nullptr)
{
}

Map::~Map()
{
}

void Map::Load(sf::Vector2i mapDimensions)
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
            int tileIndex = mapData.tiles[y][x];
            mapSprites[y][x].setTexture(tileSheetTexture);
            mapSprites[y][x].setTextureRect(sf::IntRect(
                tiles[tileIndex].position.x,
                tiles[tileIndex].position.y,
                mapData.tileWidth,
                mapData.tileHeight
            ));
            mapSprites[y][x].setPosition(sf::Vector2f(x * mapData.tileWidth * (int)mapData.scaleX* ((double)mapDimensions.x / 1920.0), 
                y * mapData.tileHeight * (int)mapData.scaleY* ((double)mapDimensions.y / 1080.0)));
            mapSprites[y][x].setScale(mapData.scaleX * ((double)mapDimensions.x/1920.0), mapData.scaleY * ((double)mapDimensions.y/1080.0));
        }
    }

    wallHitbox = new sf::RectangleShape[mapData.hitboxNumber];
    for (size_t i = 0; i < mapData.hitboxNumber; i++)
    {
        wallHitbox[i].setOutlineColor(sf::Color::Blue);
        wallHitbox[i].setOutlineThickness(-1);
        wallHitbox[i].setFillColor(sf::Color::Transparent);
        wallHitbox[i].setSize(sf::Vector2f(mapData.tileWidth*mapData.wallHitboxSizes[i].x, mapData.tileHeight*mapData.wallHitboxSizes[i].y)); //invariant
        wallHitbox[i].setPosition(sf::Vector2f(mapData.wallHitboxPositions[i].x * mapData.tileWidth * (int)mapData.scaleX * ((double)mapDimensions.x / 1920.0),
            mapData.wallHitboxPositions[i].y * mapData.tileHeight * (int)mapData.scaleY * ((double)mapDimensions.y / 1080.0))); //les 2 varient selon la résolution de l'écran
        wallHitbox[i].setScale(mapData.scaleX * ((double)mapDimensions.x / 1920.0), mapData.scaleY * ((double)mapDimensions.y / 1080.0));
    }

    std::cout << "sizeX :" << wallHitbox[0].getSize().x << " map data :" << mapData.wallHitboxPositions[0].x << std::endl;
    std::cout << "sizeY :" << wallHitbox[0].getSize().y << std::endl;
    std::cout << "posX :" << wallHitbox[0].getPosition().x << std::endl;
    std::cout << "posY :" << wallHitbox[0].getPosition().y << std::endl;
    std::cout << "scaleX :" << wallHitbox[0].getScale().x << " direct value :" << mapData.scaleX * ((double)mapDimensions.x / 1280.0) << std::endl;
    std::cout << "wallHitboxNumber :" << mapData.hitboxNumber << std::endl;

}

void Map::Update(float deltaTime, CameraService& cameraService, sf::Vector2i mapDimensions)
{
    for (size_t y = 0; y < mapData.mapHeight; y++)
    {
        for (size_t x = 0; x < mapData.mapWidth; x++)
        {
            sf::Vector2f position = sf::Vector2f(x * mapData.tileWidth * mapData.scaleX * ((double)mapDimensions.x / 1920.0),
                y * mapData.tileHeight * (int)mapData.scaleY * ((double)mapDimensions.y / 1080.0));
            cameraService.SetSprite(mapSprites[y][x], position);
            mapSprites[y][x].setScale(mapData.scaleX * ((float)mapDimensions.x / 1920.0f), mapData.scaleY * ((float)mapDimensions.y / 1080.0f));
        }
    }
    for (size_t i = 0; i < mapData.hitboxNumber; i++)
    {
        sf::Vector2f position = sf::Vector2f(mapData.wallHitboxPositions[i].x * mapData.tileWidth * (int)mapData.scaleX * ((double)mapDimensions.x / 1920.0),
            mapData.wallHitboxPositions[i].y * mapData.tileHeight * (int)mapData.scaleY * ((double)mapDimensions.y / 1080.0)); //les 2 varient selon la résolution de l'écran
        cameraService.SetRectangle(wallHitbox[i], position);
        wallHitbox[i].setScale(mapData.scaleX * ((double)mapDimensions.x / 1920.0), mapData.scaleY * ((double)mapDimensions.y / 1080.0));
    }
}

void Map::Draw(sf::RenderWindow* window)
{
    for (size_t y = 0; y < mapData.mapHeight; y++)
    {
        for (size_t x = 0; x < mapData.mapWidth; x++)
        {
            window->draw(mapSprites[y][x]);
        }
    }
    //for (size_t i = 0; i < mapData.hitboxNumber; i++)
    //{
    //    window->draw(wallHitbox[i]);
    //}
}

bool Map::ColideWithWall(sf::RectangleShape* objectHitbox) const
{
    for (size_t i = 0; i < mapData.hitboxNumber; i++)
    {
        if (objectHitbox->getGlobalBounds().intersects(wallHitbox[i].getGlobalBounds()))
            return true;
    }
    return false;
}
