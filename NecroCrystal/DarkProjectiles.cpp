#include "DarkProjectiles.h"
#include <iostream>
#include"Math.h"

void DarkProjectiles::Initialize()
{
	speed = 0.5f;
}

void DarkProjectiles::Load()
{
    if (texture.loadFromFile("Assets/Projectiles/darkProjectile.png"))
    {
        std::cout << "darkProjectile image loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "darkProjectile image failed to load" << std::endl;
    }
}

void DarkProjectiles::Update(Necromancer& necromancer)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        DarkProjectile darkProjectile;
        darkProjectile.Initialize();
        darkProjectile.Load();
        darkProjectile.sprite.setTexture(texture); //à mettre dans Load quand je saurai passer paar référence
        darkProjectile.sprite.setPosition(necromancer.sprite.getPosition() + sf::Vector2f(64, 20));
        projectiles.push_back(darkProjectile);
    }
    for (size_t i = 0; i < projectiles.size(); i++)
    {
        sf::Vector2f direction = Math::convertVector(sf::Mouse::getPosition()) - projectiles[i].sprite.getPosition();
        projectiles[i].sprite.setPosition(projectiles[i].sprite.getPosition() + Math::normalizeVector(direction) * speed);
    }
}

void DarkProjectiles::Draw(sf::RenderWindow& window)
{

    for (size_t i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].Draw(window);
    }
}
