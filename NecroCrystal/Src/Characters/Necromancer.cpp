#include "Necromancer.h"
#include"../Utilities/Math.h"
#include <iostream>

Necromancer::Necromancer() :
    width(64),height(64),speed(0.25f)
{
}

Necromancer::~Necromancer()
{
}

void Necromancer::Load(int xSize, int ySize)
{
    if (texture.loadFromFile("Assets/Player/Textures/necromancerWalking.png"))
    {
        std::cout << "Necromancer image loaded successfully" << std::endl;
        sprite.setTexture(texture);

        int XNIndex = 0;
        int YNIndex = 0;
        sprite.setTextureRect(sf::IntRect(XNIndex * width, YNIndex * height, width, height));
        sprite.scale(sf::Vector2f(scale, scale));//multiplie la taille par 3
        sprite.setPosition(sf::Vector2f(xSize / 2, ySize / 2));
    }
    else
    {
        std::cout << "Necromancer image failed to load" << std::endl;
    }
    
}

void Necromancer::Update(FireMage& fireMage,float deltaTime,sf::RenderWindow& window)
{
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2f horizontal_change = sf::Vector2f(0, 0);
    sf::Vector2f vertical_change = sf::Vector2f(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        horizontal_change += sf::Vector2f(1, 0)*speed*deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        horizontal_change -= sf::Vector2f(1, 0)*speed*deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
         vertical_change -= sf::Vector2f(0, 1) * speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        vertical_change += sf::Vector2f(0, 1) * speed * deltaTime;
    }
    sprite.setPosition(position+vertical_change+horizontal_change);
    //TODO faire qu'on va un peu moins vite en diagonale (mais toujours un peu plus vite qu'en ligne droite)
    //actuellement, on va 40% plus vite en ligne droite, on pourrait le passer � 20%
    
    window.setPosition(window.getPosition()+sf::Vector2i(vertical_change));
    //un gros fail, une autre id�e pourrait �tre d'avoir un vector 2f qui se balade partout et qui contient les variations d'�cran
    //de la frame actuelle, ou de celle d'avant
    //soit on change tout au fur et � mesure(moins pratique), sont on change tout � la fin (plus long)

    //id�e, cr�er une nouvelle fonction qui remplace .setPosition et qui prend en compe les changmeent de window 
    // (c'est vraiment une super id�e) 

    if (Math::SpriteCollision(sprite, fireMage.sprite))
    {
        std::cout << "COLLISION !!!!" << std::endl;
    }
}

void Necromancer::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}