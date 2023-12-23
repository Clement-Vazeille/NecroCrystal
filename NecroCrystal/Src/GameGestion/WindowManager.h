#pragma once
#include <SFML/Graphics.hpp>
class WindowManager
{
private:
	sf::VideoMode fullScreenMode;
	sf::VideoMode desktopMode;

	sf::RenderWindow* fullScreenWindow;
	sf::RenderWindow* desktopWindow;
	bool isGameFullScreen;

	double timer;
	double refreshTime;

public:
	sf::Vector2i size;

public:
	WindowManager();

	void Load();
	void Update(double deltaTime);
	sf::RenderWindow* GetWindow();
};

