#pragma once
#include <SFML/Graphics.hpp>
#include "../Utilities/CameraService.h"
#include <vector>

class Character
{
protected:
	sf::Texture texture;
	int width;
	int height;    //before applying the scale
	float scale;
	int health;
	float speed;
	int faction;  //pourrait se faire avec un enum
	//0 pour neutre/invincible, 1 pour avec le nécro, 2 pour méchant

	bool show_hitboxes = true;
	
	int spriteNumber;
	sf::Sprite* sprites;
	sf::RectangleShape hitbox;

public:
	Character();
	~Character();

	virtual void Load(sf::Vector2i& windowDimensions)=0;
	virtual void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime)=0; //rajouter l'entity list
	bool SetHealth(int hp); //renvoi true si le character meurt
	int GetHealth(void) const;
	void Draw(sf::RenderWindow* window) const;

	sf::Sprite& getSprite(void) const;
	int getFaction(void) const;

	sf::RectangleShape* getHitbox(void);
	
};

