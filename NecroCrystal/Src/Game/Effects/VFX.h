#pragma once
#include <SFML/Graphics.hpp>

#include"../Utilities/CameraService.h"
#include "../Utilities/Animation.h"
#include "VFXdata.h"

class VFX
{
protected:
	sf::Sprite sprite;
	Animation animation;
	int scale;

	float speed;

	sf::Vector2f target;
	bool followTarget;        //is the vfx following a target
	float maxTimer;				//a VFX disappear when it hits its target or when the timer get to maxTimer
	float timer;               
	bool endOnTimer;			//does the vfx has a timer
public:
	VFX(VFXdata& vFXdata );
	void Load(sf::Vector2i& windowDimensions, sf::Vector2f position, sf::Vector2f givenTarget,sf::Texture& texture);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime);
	void Draw(sf::RenderWindow* window) const;
	bool ShouldBeDeleted(sf::Vector2i& windowDimensions) const;
};

