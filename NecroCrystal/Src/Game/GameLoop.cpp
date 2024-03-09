#include "GameLoop.h"
#include <iostream>

#include "Characters/Enemy/Enemy.h"
#include "Characters/Enemy/MeleeMage.h"
#include "Characters/Enemy/CrazyFireMage.h"
#include "Characters/Enemy/KnightCaptain.h"

void GameLoop::LoadWave(MapData* mapData, sf::Vector2i& windowDimensions)
{
    int endEnemy = mapData->enemyNumber;
    if (currentWave + 1 < mapData->waveNumber)
        endEnemy = mapData->waveEnemyIndex[currentWave + 1]; //if it is not the last wave we go till just before beginning of next wave

    for (size_t i = mapData->waveEnemyIndex[currentWave]; i < endEnemy; i++)
    {
        if (mapData->enemyTypes[i] == 0) //type 0 is fire mage
        {
            Character* enemy = new FireMage;
            enemy->Load(windowDimensions, cameraService.SetVector(mapData->enemyPositions[i]));
            characters.push_back(enemy);
        }
        if (mapData->enemyTypes[i] == 1) //type 1 is melee mage
        {
            Character* enemy = new MeleeMage;
            enemy->Load(windowDimensions, cameraService.SetVector(mapData->enemyPositions[i]));
            characters.push_back(enemy);
        }
        if (mapData->enemyTypes[i] == 2) //type 2 is crazy fire mage
        {
            Character* enemy = new CrazyFireMage;
            enemy->Load(windowDimensions, cameraService.SetVector(mapData->enemyPositions[i]));
            characters.push_back(enemy);
        }
        if (mapData->enemyTypes[i] == 3) //type 3 is knight captain
        {
            Character* enemy = new KnightCaptain;
            enemy->Load(windowDimensions, cameraService.SetVector(mapData->enemyPositions[i]));
            characters.push_back(enemy);
        }
    }
}

GameLoop::GameLoop(sf::Vector2i windowSize) : 
    cameraService(windowSize),currentWave(0)
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
    map.Load(windowDimensions,mapFileName);
    MapData* mapData = map.getData();
    skeltonHandler.Load();
    vFXHandler.LoadTextures();

    Character* necromancer = new Necromancer;
    necromancer->Load(windowDimensions,mapData->necroSpawn);
    characters.push_back(necromancer);
    
    this->LoadWave(mapData, windowDimensions);
}

int GameLoop::update(float deltaTime,sf::Vector2i& windowDimensions,sf::Vector2f& mousePosition,std::string timerString)
{
    frameRate.Update(deltaTime);
    gameTimer.Update(windowDimensions,timerString);
    map.Update(deltaTime, cameraService,windowDimensions);
    skeltonHandler.Update(cameraService, windowDimensions, deltaTime, map, characters,randomLSFR,vFXHandler);
    if (projectileHandler.Update(characters, deltaTime, mousePosition, cameraService, windowDimensions, map,skeltonHandler,vFXHandler))
        return 2; //means game over
    
    hitboxDisplay.Update(deltaTime);

    bool isWaveCleared = true;  //les enemis peuvent uniquement mourir dans projectile Handler, donc on peut bien check ça pendnat l'update des chars
    for (auto it = std::begin(characters); it != std::end(characters); it++)
    {
        if ((*it)->getFaction() != 1 && (*it)->getFaction() != -1) //faction 1 is the necromancer faction
            isWaveCleared = false;
        (*it)->Update(cameraService, windowDimensions, deltaTime,map,characters,randomLSFR,vFXHandler);
    }

    vFXHandler.Update(cameraService, windowDimensions, deltaTime);
    vFXHandler.DeleteExpiredVFX(windowDimensions);

    if (isWaveCleared)
    {
        currentWave++;
        if (currentWave >= map.getData()->waveNumber)
            return 1; //means level cleared
        this->LoadWave(map.getData(), windowDimensions);
    }
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
