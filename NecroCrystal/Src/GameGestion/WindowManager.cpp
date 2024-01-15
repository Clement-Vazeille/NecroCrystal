#include "WindowManager.h"
#include <iostream>

WindowManager::WindowManager() :
	isGameFullScreen(true),
	timer(0),refreshTime(600),
	fullScreenWindow(nullptr),
	desktopWindow(nullptr)
{
}

void WindowManager::Load()
{
	fullScreenMode = sf::VideoMode::getFullscreenModes()[0];
	//desktopMode = sf::VideoMode::getDesktopMode();

	//desktopWindow = new sf::RenderWindow(desktopMode, "NecroCrystal", sf::Style::Default);
	fullScreenWindow = new sf::RenderWindow(fullScreenMode, "NecroCrystal", sf::Style::Fullscreen);
	//desktopWindow->setVisible(false);
	//desktopWindow->setFramerateLimit(60);
	//fullScreenWindow->setFramerateLimit(60);

	//desktopWindow->setMouseCursorVisible(false);
	fullScreenWindow->setMouseCursorVisible(false);

	size = sf::Vector2i(fullScreenMode.width, fullScreenMode.height);


}

void WindowManager::Update(double deltaTime)
{
	//timer += deltaTime;
	//if (timer > refreshTime)
	//{
		//if(sf::Keyboard::isKeyPressed(sf::Keyboard::F11))               //change fullScreen-desktopMode
		//{
			//timer = 0;
			//isGameFullScreen = !isGameFullScreen;

			//if (isGameFullScreen)
			////{
			//	size = sf::Vector2i(fullScreenMode.width, fullScreenMode.height);
			//	fullScreenWindow->setVisible(true);
			//	//desktopWindow->setVisible(false);
			//}
			//else
			//{
				//size = sf::Vector2i(desktopMode.width, desktopMode.height);
				//fullScreenWindow->setVisible(false);
				//desktopWindow->setVisible(true);
			//}
		//}
		//if (isGameFullScreen)										 //upate window size information (for sprite positions)
		//	size = sf::Vector2i(fullScreenMode.width, fullScreenMode.height);
	//}
}

sf::RenderWindow* WindowManager::GetWindow()
{
	if (isGameFullScreen)
		return fullScreenWindow;
	return desktopWindow;
}
