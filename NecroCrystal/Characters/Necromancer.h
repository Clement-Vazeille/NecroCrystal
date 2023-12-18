#pragma once
#include <SFML/Graphics.hpp>
#include "FireMage.h"

class Necromancer
{
private:
	sf::Texture texture;
	float width = 64;
	float height = 64;
	float speed = 0.25f;

	int scale = 2;
public:
	sf::Sprite sprite;
public:
	void Initialize(); //called once per App Start
	void Load(int xSize, int ySize);       //called once per App Start
	void Update(FireMage& fireMage);     //called once per frame
	void Draw(sf::RenderWindow& window);	   //called once per frame
private:
	    
};

