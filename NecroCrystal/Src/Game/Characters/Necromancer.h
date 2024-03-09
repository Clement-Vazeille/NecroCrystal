#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy/FireMage.h"
#include "../Utilities/CameraService.h"
#include "Character.h"
#include "../World/Map.h"

class Necromancer : public Character
{
protected:
	Animation loopAnimation;
	float darkProjectileTimer;
	float darkProjectileCastSpeed;
	
	bool faceRight;

	bool necroZone;

	Animation healthAnimation;
	sf::Texture healthTexture;
	double removedNotCountedHealth;

	sf::RectangleShape wallHitbox;

	float necroZoneParticuleTimer;
	float necroZoneParticuleCooldown;
	void NecroZoneUpdate(VFXHandler& vFXHandler, sf::Vector2i& windowDimensions, RandomLSFR& randomLSFR,float deltaTime);
public:
	Necromancer();
	~Necromancer();

	void Load(sf::Vector2i& windowDimensions,sf::Vector2f position);       //called once per App Start
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, 
		RandomLSFR& randomLSFR, VFXHandler& vFXHandler);     //called once per frame
	Projectile* LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters);

	const sf::Sprite& getSprite(void) const;
	bool TakeDamage(int hp);

	bool isInNecroZone(void) const;
};

