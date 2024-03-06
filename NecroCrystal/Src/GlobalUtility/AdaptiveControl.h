#pragma once
#include <SFML/Graphics.hpp>
class AdaptiveControl
{
private:
	static bool isAzerty;
public:
	static inline void SetLayoutToAzerty(void) {isAzerty = true;}
	static inline void SetLayoutToQwerty(void) {isAzerty = false;}

	//Functions here described azerty keys
	static inline bool IsZPressed(void) 
		{ return isAzerty ? sf::Keyboard::isKeyPressed(sf::Keyboard::Z) : sf::Keyboard::isKeyPressed(sf::Keyboard::W); }

	static inline bool IsQPressed(void)
		{ return isAzerty ? sf::Keyboard::isKeyPressed(sf::Keyboard::Q) : sf::Keyboard::isKeyPressed(sf::Keyboard::A); }

	static inline bool IsSPressed(void)
		{ return isAzerty ? sf::Keyboard::isKeyPressed(sf::Keyboard::S) : sf::Keyboard::isKeyPressed(sf::Keyboard::S); }

	static inline bool IsDPressed(void)
		{ return isAzerty ? sf::Keyboard::isKeyPressed(sf::Keyboard::D) : sf::Keyboard::isKeyPressed(sf::Keyboard::D); }
};