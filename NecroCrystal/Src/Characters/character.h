#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "../World/Map.h"
#include "../Utilities/CameraService.h"

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
	
	int spriteNumber;
	sf::Sprite* sprites;
	sf::RectangleShape hitbox;

public:
	Character();
	~Character();

	virtual void Load(sf::Vector2i& windowDimensions,sf::Vector2f position)=0;
	virtual void Update(CameraService& cameraService, sf::Vector2i& windowDimensions, float deltaTime, Map& map)=0; //rajouter l'entity list
	bool SetHealth(int hp); //renvoi true si le character meurt
	int GetHealth(void) const;
	void Draw(sf::RenderWindow* window) const;
	void DrawHitbox(sf::RenderWindow* window) const;

	sf::Sprite& getSprite(void) const;
	int getFaction(void) const;

	sf::RectangleShape* getHitbox(void);
};

