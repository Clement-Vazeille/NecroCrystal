#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "../../Utilities/CameraService.h"
#include "../../Utilities/Animation.h"
#include "Enemy.h"
#include "../../World/Map.h"
class MeleeMage : public Enemy
{
protected:
	std::array<Animation, 3> animations;

	float newActionTimer;
	float newActionCooldown;
	float attackDuration;
	sf::Vector2f direction;

	float dashSpeedBoost;
	float protectSpeedBoost;
	bool canLaunchAttack;
	bool isFacingRight;

	enum Action {
		Marcher=0,
		Attaquer=1,
		Proteger=2
	};
	Action currentAction;
	void SelectNewAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR);
	void Flip(void);

public:
	MeleeMage();
	~MeleeMage();

	void Load(sf::Vector2i& windowDimensions, sf::Vector2f position);
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, 
		RandomLSFR& randomLSFR, VFXHandler& vFXHandler);

	Projectile* LaunchProjectile(float deltaTime, sf::Texture* projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters);

	const sf::Sprite& getSprite(void) const;
};

