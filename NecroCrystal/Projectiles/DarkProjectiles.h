#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "DarkProjectile.h"
#include "../Characters/Necromancer.h"
#include "../Characters/FireMage.h"

class DarkProjectiles
{
private:
	float timer;
	float castSpeed;
public:
	sf::Texture texture;
	std::vector<DarkProjectile> projectiles;
	float speed;
public:
	DarkProjectiles();

	void Load();
	void Update(Necromancer& necromancer,FireMage& firemage,double deltaTime);
	void Draw(sf::RenderWindow& window);
};

