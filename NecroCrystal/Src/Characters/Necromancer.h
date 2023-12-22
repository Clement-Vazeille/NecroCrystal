#pragma once
#include <SFML/Graphics.hpp>
#include "FireMage.h"

class Necromancer
{
private:
	sf::Texture texture;
	float width;
	float height;
	float speed;

	int scale = 2;
public:
	sf::Sprite sprite;
public:
	Necromancer();
	~Necromancer();

	void Load(int xSize, int ySize);       //called once per App Start
	void Update(FireMage& fireMage,float deltaTime,sf::RenderWindow& window);     //called once per frame
	void Draw(sf::RenderWindow& window);	   //called once per frame
private:
	    
};

