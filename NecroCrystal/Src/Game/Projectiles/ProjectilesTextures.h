#pragma once
#include <SFML/Graphics.hpp>
class ProjectilesTextures
{
private:
	sf::Texture fireBall;
	sf::Texture darkProjectile;
	sf::Texture swordSlash;
	sf::Texture explosion;
	sf::Texture hammer;
	sf::Texture captainSlash;
	sf::Texture poisonDot;
	sf::Texture laser;
	sf::Texture poisonFlaque;
public:
	ProjectilesTextures();

	void Load(void);

	inline const sf::Texture& GetFireBall(void) const { return fireBall; }
	inline const sf::Texture& GetDarkProjectile(void) const { return darkProjectile; }
	inline const sf::Texture& GetSwordSlash(void) const { return swordSlash; }
	inline const sf::Texture& GetExplosion(void) const { return explosion; }
	inline const sf::Texture& GetHammer(void) const { return hammer; }
	inline const sf::Texture& GetCaptainSlash(void) const { return captainSlash; }
	inline const sf::Texture& GetPoisonDot(void) const { return poisonDot; }
	inline const sf::Texture& GetLaser(void) const { return laser; }
	inline const sf::Texture& GetPoisonFlaque(void) const { return poisonFlaque; }
};

