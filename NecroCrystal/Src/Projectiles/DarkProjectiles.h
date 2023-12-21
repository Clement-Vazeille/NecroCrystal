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
public:
	DarkProjectiles();

	void Load();
	void Update(Necromancer& necromancer,FireMage& firemage,double deltaTime,sf::Vector2f& mousePosition);
	void Draw(sf::RenderWindow& window);
};

