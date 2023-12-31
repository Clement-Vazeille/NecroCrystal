#include "GameLoop.h"

GameLoop::GameLoop(sf::Vector2f windowSize) : cameraService(windowSize)
{
}

GameLoop::~GameLoop()
{
    for (auto it = std::begin(characters); it != std::end(characters); it++)
    {
        delete(*it);
    }
}

void GameLoop::initialize(sf::Vector2i& windowDimensions)
{
    projectileHandler.Load();
    frameRate.Load();
    map.Load(windowDimensions);
    mouseCursor.Load(windowDimensions);
    MapData* mapData = map.getData();

    Character* necromancer = new Necromancer;
    necromancer->Load(windowDimensions,mapData->necroSpawn);
    characters.push_back(necromancer);
    for (size_t i = 0; i < mapData->enemyNumber; i++)
    {
        if (mapData->enemyTypes[i] == 0) //type 0 is fire mage
        {
            Character* fireMage = new FireMage;
            fireMage->Load(windowDimensions, mapData->enemyPositions[i]);
            characters.push_back(fireMage);
        }
    }
}

int GameLoop::update(float deltaTime,sf::Vector2i& windowDimensions,sf::Vector2f& mousePosition)
{
    frameRate.Update(deltaTime);
    mouseCursor.Update(mousePosition, windowDimensions);
    map.Update(deltaTime, cameraService,windowDimensions);
    if (projectileHandler.Update(characters, deltaTime, mousePosition, cameraService, windowDimensions, map))
        return 2;
    hitboxDisplay.Update(deltaTime);

    bool isLevelCleared = true;  //les enemis peuvent uniquement mourir dans projectile Handler, donc on peut bien check �a pendnat l'update des chars
    for (auto it = std::begin(characters); it != std::end(characters); it++)
    {
        if ((*it)->getFaction() != 1) //faction 1 is the necromancer faction
            isLevelCleared = false;
        (*it)->Update(cameraService, windowDimensions, deltaTime,map,characters);
    }
    if (isLevelCleared)
        return 1;
    return 0;
}

void GameLoop::draw(sf::RenderWindow* window)
{
    map.Draw(window);

    for (auto& character : characters)
    {
        character->Draw(window);
        if (hitboxDisplay.getValue())
            character->DrawHitbox(window);
    }
    projectileHandler.Draw(window,hitboxDisplay.getValue());
    frameRate.Draw(window);
    mouseCursor.Draw(window);
}
