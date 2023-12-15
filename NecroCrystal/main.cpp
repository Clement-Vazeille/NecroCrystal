#include <iostream>

#include <SFML/Graphics.hpp>

int main()
{
    //------------------------Initialize---------------------------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8; 

    sf::RenderWindow window(sf::VideoMode(800, 600), " RPG Game ", sf::Style::Default, settings);
    sf::CircleShape shape(50.0f);
    shape.setFillColor(sf::Color::Red);
    shape.setOutlineThickness(10.0f);
    shape.setOutlineColor(sf::Color::Cyan);

    sf::RectangleShape rectangle(sf::Vector2f(100.0f, 20.0f));
    rectangle.setFillColor(sf::Color::Magenta);
    rectangle.setPosition(sf::Vector2f(110.0f, 45.0f));
    rectangle.setOrigin(rectangle.getSize() / 2.0f);
    //------------------------Initialize---------------------------------------

    while (window.isOpen())
    {
        //------------------------UPDATE---------------------------------------
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        rectangle.rotate(0.01f);
        //------------------------UPDATE---------------------------------------

        //-------------------------DRAW---------------------------------------
        window.clear(sf::Color::Black);
        window.draw(shape);
        window.draw(rectangle);
        window.display();
        //-------------------------DRAW---------------------------------------
    }

    return 0;
}