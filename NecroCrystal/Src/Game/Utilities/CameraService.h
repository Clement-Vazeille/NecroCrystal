#pragma once
#include <SFML/Graphics.hpp>

class CameraService
{
	//Pour le moment l'id�e c'est d'avoir une variable diff qui compte la ddiff�rence verticale avec la position pr�c�dente
	//On retient aussi la position absolue au cas o� ce sera utile plus tard

private:
	float diff;
	float cameraPosition;

	sf::Vector2f windowSizeMem;
	sf::Vector2f windowSizeChangeRatio;
public:
	CameraService(sf::Vector2f windowSize);

	void MoveSprite(sf::Sprite& sprite, sf::Vector2f& movement);
	void SetSprite(sf::Sprite& sprite, sf::Vector2f& position);
	void SetRectangle(sf::RectangleShape& sprite, sf::Vector2f& position);

	void Update(float new_diff, sf::Vector2f windowSize);
};

