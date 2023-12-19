#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "DarkProjectile.h"
#include "../Characters/Necromancer.h"

class DarkProjectiles
{
public:
	sf::Texture texture;
	std::vector<DarkProjectile> projectiles;
	float speed;
public:
	void Initialize();
	void Load();
	void Update(Necromancer& necromancer,float deltaTime);
	void Draw(sf::RenderWindow& window);
};

