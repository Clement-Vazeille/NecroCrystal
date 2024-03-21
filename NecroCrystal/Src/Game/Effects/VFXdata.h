#pragma once

#include <SFML/Graphics.hpp>

struct VFXdata
{
	int maxTimer;
	bool followTarget;
	bool endOnTimer;
	float speed;
	int refreshTimer;
	int frameNumber;
	int xFrameSize;
	int yFrameSize;
	float scale;
	int type;
};