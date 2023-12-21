#pragma once
#include <SFML/Graphics.hpp>
class FrameRate
{
private:
	sf::Font font;
	sf::Text text;

	double timer;
	double refreshTime;

	bool displayed;
	double displayTimer;
	double displayRefreshTime;

	
public:
	FrameRate(); //constructor
	~FrameRate(); //destructor, s'active quand l'objet est détruit

	void Load();
	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);
};

