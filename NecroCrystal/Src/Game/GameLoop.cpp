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

void GameLoop::initialize(sf::Vector2i& windowDimensions,TextManager& textManager)
{
    projectileHandler.Load();
    frameRate.Load();
    gameTimer.Initialize(textManager);
    map.Load(windowDimensions);
    mouseCursor.Load(windowDimensions);
    MapData* mapData = map.getData();
    skeltonHandler.Load();

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

int GameLoop::update(float deltaTime,sf::Vector2i& windowDimensions,sf::Vector2f& mousePosition,std::string timerString)
{
    frameRate.Update(deltaTime);
    gameTimer.Update(windowDimensions,timerString);
    mouseCursor.Update(mousePosition, windowDimensions);
    map.Update(deltaTime, cameraService,windowDimensions);
    skeltonHandler.Update(cameraService, windowDimensions, deltaTime, map, characters);
    if (projectileHandler.Update(characters, deltaTime, mousePosition, cameraService, windowDimensions, map,skeltonHandler))
        return 2; //means game over
    hitboxDisplay.Update(deltaTime);

    bool isLevelCleared = true;  //les enemis peuvent uniquement mourir dans projectile Handler, donc on peut bien check ça pendnat l'update des chars
    for (auto it = std::begin(characters); it != std::end(characters); it++)
    {
        if ((*it)->getFaction() != 1) //faction 1 is the necromancer faction
            isLevelCleared = false;
        (*it)->Update(cameraService, windowDimensions, deltaTime,map,characters);
    }
    if (isLevelCleared)
        return 1; // means wp gg
    return 0;
}

void GameLoop::draw(sf::RenderWindow* window)
{
    map.Draw(window);
    skeltonHandler.DrawSkeletons(window, hitboxDisplay.getValue());

    for (auto character : characters)
    {
        character->Draw(window);
        if (hitboxDisplay.getValue())
            character->DrawHitbox(window);
    }
    projectileHandler.Draw(window,hitboxDisplay.getValue());

    characters[0]->Draw(window); // put necro in front of enemies and projectile

    frameRate.Draw(window);
    gameTimer.Draw(window);

    mouseCursor.Draw(window);
}
