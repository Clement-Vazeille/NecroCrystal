#pragma once
#include "character.h"
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <array>

#include "Enemy/FireMage.h"
#include "../Utilities/CameraService.h"
#include "Character.h"
#include "../World/Map.h"
#include "../Utilities/Animation.h"

//je vais tr�s surement devoir faire une classe skeleton handler, liste des squelettes, contient la texture, lvl up ? 

class Skeleton : public Character
{
protected:
	bool faceRight;
	bool moving;
	float stopDistance;

	std::unordered_set<int> enemyDashed; //contain all enemy hitted on current dash
	bool activated;
	float activatedTimer;
	float activationTime;
	float spawnAnimationDuration;

	float attackTimer;
	float attackDuration;

	sf::Vector2f target; //if we want him to reach the target directly we could slow him just before he hit the target

	long aD; //attackDamage
	long dashAD; //Dash damages, < aD
	long damageDealt;

	sf::Vector2f dashKillPosition;

	std::array<Animation, 4> skeletonAnimations;
	std::array<Animation, 4> spearAnimations;
	std::array<Animation, 4> armorAnimations;
	int currentAnimation;
	int skeletonLevel; 
	//0 = wooden
	//1 = gold
	int goldDamageRequirement;
	//2 = purple (not possible actually)

	void DealDamage(int damageDealt);
	void FlipSkeleton(void);

public:
	Skeleton();
	~Skeleton();

	void Load(sf::Vector2i& windowDimensions, sf::Vector2f position);   //never call this, inherited from character polymorphism
	void Load(sf::Vector2i& windowDimensions, sf::Vector2f position, sf::Texture& texture); //for when is called by SkeletonHandler
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, 
		RandomLSFR& randomLSFR, VFXHandler& vFXHandler);     //called once per frame
	Projectile* LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters, VFXHandler& vFXHandler);

	void AttackAnimation(sf::Vector2f target);
	void StartDash(sf::Vector2f mousePosition);

	const sf::Sprite& getSprite(void) const;
	bool TakeDamage(int hp);
	bool IsActivated(void) const;
	bool IsDrawn(void) const;
	const float GetAD(void) const;

	sf::Vector2f HasDashKilledSomething(void);
};

