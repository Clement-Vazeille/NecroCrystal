#include "Map.h"
#include <iostream>
#include "MapLoader.h"

Map::Map():
    totalTilesX(0),totalTilesY(0),
    tiles(nullptr),wallHitbox(nullptr)
{
}

Map::~Map()
{
    if (tiles != nullptr)
        delete tiles;

    delete mapData.wallHitboxPositions;
    delete mapData.wallHitboxSizes;
    delete mapData.enemyPositions;
    delete mapData.enemyTypes;
    delete mapData.waveEnemyIndex;

    for (size_t i = 0; i < mapData.mapHeight; i++)
    {
        delete mapData.tiles[i];
    }
    delete mapData.tiles;

}

void Map::Load(sf::Vector2i mapDimensions,std::string& mapFileName)
{
    MapLoader::Load(mapFileName, mapData);
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

    mapSprites.resize(mapData.mapHeight);
    for (size_t y = 0; y < mapData.mapHeight; y++)
    {
        mapSprites.at(y).resize(mapData.mapWidth);
        for (size_t x = 0; x < mapData.mapWidth; x++)
        {
            int tileIndex = mapData.tiles[y][x];
            mapSprites.at(y).at(x).setTexture(tileSheetTexture);
            mapSprites.at(y).at(x).setTextureRect(sf::IntRect(
                tiles[tileIndex].position.x,
                tiles[tileIndex].position.y,
                mapData.tileWidth,
                mapData.tileHeight
            ));
            mapSprites.at(y).at(x).setPosition(sf::Vector2f(x * mapData.tileWidth * (int)mapData.scaleX* ((double)mapDimensions.x / 1920.0),
                y * mapData.tileHeight * (int)mapData.scaleY* ((double)mapDimensions.y / 1080.0)));
            mapSprites.at(y).at(x).setScale(mapData.scaleX * ((double)mapDimensions.x/1920.0), mapData.scaleY * ((double)mapDimensions.y/1080.0));
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
            mapData.wallHitboxPositions[i].y * mapData.tileHeight * (int)mapData.scaleY * ((double)mapDimensions.y / 1080.0))); //les 2 varient selon la r�solution de l'�cran
        wallHitbox[i].setScale(mapData.scaleX * ((double)mapDimensions.x / 1920.0), mapData.scaleY * ((double)mapDimensions.y / 1080.0));
    }
}

void Map::Update(float deltaTime, CameraService& cameraService, sf::Vector2i mapDimensions)
{
    for (size_t y = 0; y < mapData.mapHeight; y++)
    {
        for (size_t x = 0; x < mapData.mapWidth; x++)
        {
            sf::Vector2f position = sf::Vector2f(x * mapData.tileWidth * mapData.scaleX * ((double)mapDimensions.x / 1920.0),
                y * mapData.tileHeight * (int)mapData.scaleY * ((double)mapDimensions.y / 1080.0));
            cameraService.SetSprite(mapSprites.at(y).at(x), position);
            mapSprites.at(y).at(x).setScale(mapData.scaleX * ((float)mapDimensions.x / 1920.0f), mapData.scaleY * ((float)mapDimensions.y / 1080.0f));
        }
    }
    for (size_t i = 0; i < mapData.hitboxNumber; i++)
    {
        sf::Vector2f position = sf::Vector2f(mapData.wallHitboxPositions[i].x * mapData.tileWidth * (int)mapData.scaleX * ((double)mapDimensions.x / 1920.0),
            mapData.wallHitboxPositions[i].y * mapData.tileHeight * (int)mapData.scaleY * ((double)mapDimensions.y / 1080.0)); //les 2 varient selon la r�solution de l'�cran
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
            window->draw(mapSprites.at(y).at(x));
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

MapData* Map::getData(void)
{
    return &mapData;
}
