#pragma once
#include <SFML/Graphics.hpp>

class CameraService
{
	//L'idee c'est d'avoir une variable diff qui compte la difference verticale avec la position presente
	//On retient aussi la position absolue au cas ou ce sera utile un jour

private:
	float diff;
	float cameraPosition;

	sf::Vector2f windowSizeMem;
	sf::Vector2f windowSizeChangeRatio;
public:
	CameraService(sf::Vector2i windowSize);

	void MoveSprite(sf::Sprite& sprite, sf::Vector2f& movement);
	void SetSprite(sf::Sprite& sprite, sf::Vector2f& position);
	void SetRectangle(sf::RectangleShape& sprite, sf::Vector2f& position);
	void UpdateVector(sf::Vector2f& vector);

	float GetDiff(void) const;
	float GetCameraPosition(void) const;

	sf::Vector2f SetVector(sf::Vector2f vector);

	void Update(float new_diff, sf::Vector2f windowSize);
};

