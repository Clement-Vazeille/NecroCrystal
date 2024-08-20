#include "Pestimus.h"
#include <iostream>
#include "../Necromancer.h"
#include "../../Utilities/Math.h"

void Pestimus::SelectNewAttackAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR)
{
}

void Pestimus::SelectNewMovementAction(sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR)
{
}

void Pestimus::Flip(void)
{
	for (auto& animation : animations)
	{
		animation.Flip();
	}
}

Pestimus::Pestimus()
{
}

Pestimus::~Pestimus()
{
}

void Pestimus::Load(sf::Vector2i& windowDimensions, sf::Vector2f position)
{
}

void Pestimus::Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR, VFXHandler& vFXHandler)
{
}

Projectile* Pestimus::LaunchProjectile(float deltaTime, ProjectilesTextures& projectilesTextures, sf::Vector2i windowDimensions, sf::Vector2f mousePosition, std::vector<Character*>& characters)
{
	return nullptr;
}

const sf::Sprite& Pestimus::getSprite(void) const
{
	// TODO: insérer une instruction return ici
}

bool Pestimus::TakeDamage(int hp)
{
	return false;
}
