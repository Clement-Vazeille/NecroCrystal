#pragma once
#include <SFML/Graphics.hpp>
#include "FireMage.h"
#include "../Utilities/CameraService.h"

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

	void Load(sf::Vector2i& windowDimensions);       //called once per App Start
	void Update(FireMage& fireMage,float deltaTime,CameraService& cameraService);     //called once per frame
	void Draw(sf::RenderWindow* window);	   //called once per frame
private:
	    
};

