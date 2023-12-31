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
	

	std::vector<Projectile*> projectiles;

	//textures
	sf::Texture* projectilesTextures;
	int textureNumber;

	bool ProjectileCollisionChecker(Projectile* projectile,std::vector<Character*>& characters, Map& map, bool& isNecroDead);
public:
	ProjectilesHandler();

	void Load();
	bool Update(std::vector<Character*>& characters, double deltaTime, sf::Vector2f& mousePosition, CameraService& cameraService, sf::Vector2i& windowDimensions,Map& map);
	//return true if necromancer died

	void Draw(sf::RenderWindow* window,bool drawHitbox) const;
	
};

