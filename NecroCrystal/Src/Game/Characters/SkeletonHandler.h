#pragma once
#include <vector>
#include "Skeleton.h"
class SkeletonHandler
{
private:
	sf::Texture texture;
	std::vector<Skeleton*> skeletons;

	float skeletonRange;

	float skeletonDashTimer; //I should made a class for Timer Cooldown
	float skeletonDashCooldown;
public:
	SkeletonHandler();
	~SkeletonHandler();

	void Load(void);
	void SpawnSkeleton(sf::Vector2i& windowDimensions, sf::Vector2f position);
	void SkeletonAttack(Character* character); //upgrade here ?
	void SkeletonDash(sf::Vector2f posititon,float deltaTime); //pas besoin de prendre le milieu
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters);
	void DrawSkeletons(sf::RenderWindow* window,bool showHitbox) const;
};

