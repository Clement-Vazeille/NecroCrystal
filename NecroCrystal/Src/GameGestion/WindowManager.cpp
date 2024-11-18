#include "WindowManager.h"
#include <iostream>

WindowManager::WindowManager() :
	isGameFullScreen(true),
	timer(0),refreshTime(600),
	fullScreenWindow(nullptr),
	desktopWindow(nullptr)
{
}

WindowManager::~WindowManager()
{
	if (fullScreenWindow != nullptr)
		delete fullScreenWindow;
}

void WindowManager::Load()
{

	// Créer une fenêtre SFML
	fullScreenWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "NecroCrystal",sf::Style::Fullscreen);
	fullScreenWindow->setMouseCursorVisible(false);
	size = sf::Vector2i(1920, 1080);
	

	//fullScreenMode = sf::VideoMode::getFullscreenModes()[0];
	//fullScreenWindow = new sf::RenderWindow(fullScreenMode, "NecroCrystal", sf::Style::Fullscreen);
	//fullScreenWindow->setMouseCursorVisible(false);
	//size = sf::Vector2i(fullScreenMode.width, fullScreenMode.height);


}

void WindowManager::Update(double deltaTime)
{
	// Adapter la résolution de la fenêtre à l'écran
	sf::Vector2u screenSize = sf::Vector2u(sf::VideoMode::getDesktopMode().width,
		sf::VideoMode::getDesktopMode().height);

	// Calculez la nouvelle résolution en maintenant le ratio d'aspect
	float aspectRatio = static_cast<float>(screenSize.x) / static_cast<float>(screenSize.y);
	sf::Vector2u newResolution(static_cast<unsigned int>(screenSize.x),
		static_cast<unsigned int>(screenSize.x / aspectRatio));

	// Add la nouvelle résolution
	fullScreenWindow->setSize(newResolution);

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
