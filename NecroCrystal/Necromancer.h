#pragma once
#include <SFML/Graphics.hpp>

class Necromancer
{
private:
	sf::Texture texture;
public:
	sf::Sprite sprite;
public:
	void Initialize(); //called once per App Start
	void Load(int xSize, int ySize);       //called once per App Start
	void Update();     //called once per frame
	void Draw(sf::RenderWindow& window);	   //called once per frame
private:
	    
};

