#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "DarkProjectile.h"
#include "../Characters/Necromancer.h"
#include "../Characters/Enemy/FireMage.h"
#include "../Utilities/CameraService.h"

class DarkProjectiles
{
private:
	float timer;
	float castSpeed;
public:
	sf::Texture texture;
	std::vector<DarkProjectile> projectiles;
public:
	DarkProjectiles();

	void Load();
	void Update(Necromancer& necromancer,FireMage& firemage,double deltaTime,sf::Vector2f& mousePosition, CameraService& cameraService);
	void Draw(sf::RenderWindow* window);
};

