#pragma once
#include <SFML/Graphics.hpp>
class FireMage
{
private:
	sf::Texture texture;
	int width = 64;
	int height = 64;
	int scale = 2;
public:
	sf::Sprite sprite;
public:
	void Initialize();
	void Load(int x, int y);
	void Update();
	void Draw(sf::RenderWindow& window);
};

