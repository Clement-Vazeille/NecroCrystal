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
    map.Load(windowDimensions);    //devrait load les ennemis

    Character* necromancer = new Necromancer;
    necromancer->Load(windowDimensions);

    Character* fireMage = new FireMage;
    fireMage->Load(windowDimensions);

    characters.push_back(necromancer);
    characters.push_back(fireMage);

}

void GameLoop::update(float deltaTime,sf::Vector2i& windowDimensions,sf::Vector2f& mousePosition)
{
    frameRate.Update(deltaTime);
    map.Update(deltaTime, cameraService,windowDimensions);
    projectileHandler.Update(characters, deltaTime, mousePosition, cameraService, windowDimensions,map);
    
    for (auto it = std::begin(characters); it != std::end(characters); it++)
    {
        (*it)->Update(cameraService, windowDimensions, deltaTime,map);
    }
}

void GameLoop::draw(sf::RenderWindow* window)
{
    map.Draw(window);

    for (auto& character : characters)
    {
        character->Draw(window);
    }
    projectileHandler.Draw(window);

    frameRate.Draw(window);
}
