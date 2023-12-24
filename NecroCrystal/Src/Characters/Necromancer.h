#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy/FireMage.h"
#include "../Utilities/CameraService.h"

class Necromancer
{
protected:
	sf::Texture texture;
	float width;
	float height;
	float speed;

	int scale = 2;
public:
	sf::Sprite sprite; //TODO :  l'encapsuler
public:
	Necromancer();
	~Necromancer();

	void Load(sf::Vector2i& windowDimensions);       //called once per App Start
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime);     //called once per frame
	void Draw(sf::RenderWindow* window);	   //called once per frame
};

