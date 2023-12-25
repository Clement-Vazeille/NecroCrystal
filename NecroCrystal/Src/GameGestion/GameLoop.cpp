#include "GameLoop.h"

GameLoop::GameLoop()
{
}

GameLoop::~GameLoop()
{
    for (auto it = std::begin(characters); it != std::end(characters); it++)
    {
        free(*it);
    }
}

void GameLoop::initialize(sf::Vector2i& windowDimensions)
{
    projectileHandler.Load();
    frameRate.Load();
    map.Load();    //devrait load les ennemis

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
    map.Update(deltaTime, cameraService);
    projectileHandler.Update(characters, deltaTime, mousePosition, cameraService, windowDimensions);
    
    for (auto it = std::begin(characters); it != std::end(characters); it++)
    {
        (*it)->Update(cameraService, windowDimensions, deltaTime);
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
