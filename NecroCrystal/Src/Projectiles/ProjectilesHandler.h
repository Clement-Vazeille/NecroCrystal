#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h"
#include "../Characters/Character.h"
#include "../Utilities/CameraService.h"
#include "../World/Map.h"

class ProjectilesHandler
{
protected:
	float timer;
	float darkProjectileCastSpeed;

	std::vector<Projectile*> projectiles;

	//textures
	sf::Texture darkProjectileTexture;

	bool ProjectileCollisionChecker(Projectile* projectile,std::vector<Character*>& characters, Map& map);
public:
	ProjectilesHandler();

	void Load();
	void Update(std::vector<Character*>& characters, double deltaTime, sf::Vector2f& mousePosition, CameraService& cameraService, sf::Vector2i& windowDimensions,Map& map);
	void Draw(sf::RenderWindow* window) const;
	
};

