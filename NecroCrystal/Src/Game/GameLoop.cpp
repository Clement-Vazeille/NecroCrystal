#include "GameLoop.h"
#include <iostream>

#include "Characters/Enemy/Enemy.h"
#include "Characters/Enemy/MeleeMage.h"
GameLoop::GameLoop(sf::Vector2i windowSize) : cameraService(windowSize)
{
    Enemy::enemyNumber = 0;
}

GameLoop::~GameLoop()
{
    for (auto& character : characters)
    {
        delete character;
    }
}

void GameLoop::initialize(sf::Vector2i& windowDimensions,TextManager& textManager,std::string& mapFileName)
{
    projectileHandler.Load();
    frameRate.Load();
    gameTimer.Initialize(textManager);
    std::cout << "balise 1" << std::endl;
    map.Load(windowDimensions,mapFileName);
    std::cout << "balise 2" << std::endl;
    MapData* mapData = map.getData();
    skeltonHandler.Load();
    vFXHandler.LoadTextures();

    Character* necromancer = new Necromancer;
    necromancer->Load(windowDimensions,mapData->necroSpawn);
    characters.push_back(necromancer);
    for (size_t i = 0; i < mapData->enemyNumber; i++)
    {
        //std::cout << "enemy pushed" << std::endl;
        if (mapData->enemyTypes[i] == 0) //type 0 is fire mage
        {
            Character* fireMage = new FireMage;
            fireMage->Load(windowDimensions, mapData->enemyPositions[i]);
            characters.push_back(fireMage);
        }
        if (mapData->enemyTypes[i] == 1) //type 0 is fire mage
        {
            Character* meleeMage = new MeleeMage;
            meleeMage->Load(windowDimensions, mapData->enemyPositions[i]);
            characters.push_back(meleeMage);
        }
    }

}

int GameLoop::update(float deltaTime,sf::Vector2i& windowDimensions,sf::Vector2f& mousePosition,std::string timerString)
{
    frameRate.Update(deltaTime);
    gameTimer.Update(windowDimensions,timerString);
    map.Update(deltaTime, cameraService,windowDimensions);
    skeltonHandler.Update(cameraService, windowDimensions, deltaTime, map, characters);
    if (projectileHandler.Update(characters, deltaTime, mousePosition, cameraService, windowDimensions, map,skeltonHandler,vFXHandler))
        return 2; //means game over
    
    hitboxDisplay.Update(deltaTime);

    bool isLevelCleared = true;  //les enemis peuvent uniquement mourir dans projectile Handler, donc on peut bien check ça pendnat l'update des chars
    for (auto it = std::begin(characters); it != std::end(characters); it++)
    {
        if ((*it)->getFaction() != 1) //faction 1 is the necromancer faction
            isLevelCleared = false;
        (*it)->Update(cameraService, windowDimensions, deltaTime,map,characters);
    }
    vFXHandler.Update(cameraService, windowDimensions, deltaTime);
    vFXHandler.DeleteExpiredVFX(windowDimensions);
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
    vFXHandler.DrawVFX(window);

    frameRate.Draw(window);
    gameTimer.Draw(window);

}
