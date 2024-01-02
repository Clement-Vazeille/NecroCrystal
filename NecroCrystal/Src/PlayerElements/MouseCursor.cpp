#include "MouseCursor.h"
#include <iostream>

MouseCursor::MouseCursor() : scale(2)
{
}

MouseCursor::~MouseCursor()
{
}

void MouseCursor::Load(sf::Vector2i& windowDimensions)
{
    if (texture.loadFromFile("Assets/Player/cursor/cursor.png"))
    {
        std::cout << "Mouse cursor loaded successfully" << std::endl;
        sprite.setTexture(texture);

        sprite.scale(sf::Vector2f(scale * ((double)windowDimensions.x / 1920.0), scale * ((double)windowDimensions.y / 1080.0)));

    }
    else
    {
        std::cout << "Mouse cursor failed to load" << std::endl;
    }
}

void MouseCursor::Update(sf::Vector2f position, sf::Vector2i& windowDimensions)
{
    sprite.setPosition(position.x - (sprite.getScale().x*texture.getSize().x/2), position.y - (sprite.getScale().y * texture.getSize().y / 2));
}

void MouseCursor::Draw(sf::RenderWindow* window) const
{
    window->draw(sprite);
}
