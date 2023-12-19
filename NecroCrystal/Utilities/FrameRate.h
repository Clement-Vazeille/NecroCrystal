#pragma once
#include <SFML/Graphics.hpp>
class FrameRate
{
private:
	sf::Font font;
	sf::Text text;

	float timer;
	float refreshTime;

	
public:
	FrameRate(); //constructor
	~FrameRate(); //destructor

	void Initialize();
	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

