#pragma once
#include <SFML/Graphics.hpp>
class FrameRate
{
private:
	sf::Font font;
	sf::Text text;

	double timer;
	double refreshTime;

	double fpsSum;  //pour moyenner le r�sultat
	int fpsNumber;

	bool displayed;
	double displayTimer;
	double displayRefreshTime;

	
public:
	FrameRate(); //constructor
	~FrameRate(); //destructor, s'active quand l'objet est d�truit

	void Load();
	void Update(double deltaTime);
	void Draw(sf::RenderWindow* window);
};

