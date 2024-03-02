#pragma once
#include <SFML/Graphics.hpp>
#include "../GlobalUtility/TextManager.h"
#include "../GlobalUtility/Sentence.h"
#include "../Game/Utilities/Animation.h"
class DeathLoop
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	Sentence* necroCrystalText;
	Animation loopAnimation;

	float sceneDuration;
	float sceneTimer;

	void Reset(void);

public:
	DeathLoop();
	~DeathLoop();

	void Initialize(sf::Vector2i& windowDimensions, TextManager& textManager);
	bool Update(float deltaTime, sf::Vector2i& windowDimensions); //true if scene is finished
	void Draw(sf::RenderWindow* window);
};

