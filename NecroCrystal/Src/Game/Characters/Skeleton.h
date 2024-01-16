#pragma once
#include "character.h"
#include <SFML/Graphics.hpp>
#include "Enemy/FireMage.h"
#include "../Utilities/CameraService.h"
#include "Character.h"
#include "../World/Map.h"

//je vais tr�s surement devoir faire une classe skeleton handler, liste des squelettes, contient la texture, lvl up ? 

class Skeleton : public Character
{
protected:
	bool faceRight;

	bool activated;
	float activatedTimer;
	float activationTime;

public:
	Skeleton();
	~Skeleton();

	void Load(sf::Vector2i& windowDimensions, sf::Vector2f position);       //never called but works
	void Load(sf::Vector2i& windowDimensions, sf::Vector2f position, sf::Texture& texture); //for when is called by SkeletonHandler
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters);     //called once per frame
	Projectile* LaunchProjectile(float deltaTime, sf::Texture* projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters);

	sf::Sprite& getSprite(void) const;
	bool SetHealth(int hp);
	bool IsActivated(void) const;
};

