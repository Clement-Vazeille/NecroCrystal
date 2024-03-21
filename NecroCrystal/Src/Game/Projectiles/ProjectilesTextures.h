#pragma once
#include <SFML/Graphics.hpp>
class ProjectilesTextures
{
private:
	sf::Texture fireBall;
	sf::Texture darkProjectile;
	sf::Texture swordSlash;
	sf::Texture explosion;
public:
	ProjectilesTextures();

	void Load(void);

	inline const sf::Texture& GetFireBall(void) const { return fireBall; }
	inline const sf::Texture& GetDarkProjectile(void) const { return darkProjectile; }
	inline const sf::Texture& GetSwordSlash(void) const { return swordSlash; }
	inline const sf::Texture& GetExplosion(void) const { return explosion; }
};

