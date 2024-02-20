#pragma once
#include <vector>
#include "Skeleton.h"

#include "../Effects/VFXHandler.h"
class SkeletonHandler
{
private:
	sf::Texture texture;
	std::vector<Skeleton*> skeletons;

	float skeletonRange;

	bool isRightClickClicked; 
public:
	SkeletonHandler();
	~SkeletonHandler();

	void Load(void);
	void SpawnSkeleton(sf::Vector2i& windowDimensions, sf::Vector2f position);
	void SkeletonAttack(Character* character,VFXHandler& vFXHandler, sf::Vector2i& windowDimensions);
	void SkeletonDash(sf::Vector2f posititon,float deltaTime); //pas besoin de prendre le milieu
	void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map, std::vector<Character*>& characters, RandomLSFR& randomLSFR);
	void DrawSkeletons(sf::RenderWindow* window,bool showHitbox) const;
};

