#pragma once
#include <vector>
#include "Skeleton.h"
class SkeletonHandler
{
private:
	sf::Texture texture;
	std::vector<Skeleton> skeletonList;
public:
	SkeletonHandler();
	~SkeletonHandler();
	void Load(void);
	void SpawnSkeleton(sf::Vector2i& windowDimensions, sf::Vector2f position);
	void SkeletonAttack(Character* character); //upgrade here ?
	void SkeletonDash(sf::Vector2f posititon); //pas besoin de prendre le milieu
};

