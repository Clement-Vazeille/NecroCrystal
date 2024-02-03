#include "Bouton.h"

Bouton::Bouton() :
	boutonText(nullptr), scale(2.f)
{
}

Bouton::~Bouton()
{
	delete boutonText;
}

void Bouton::Initialise(Sentence* sentence, sf::Vector2f hitboxPosition, sf::Vector2f hitboxSize, sf::Vector2f windowDimensions, sf::Vector2f textPosistionRatio)
{
	boutonText = sentence; // on suppose que sentence est déjà initialisé
	hitbox.setPosition(sf::Vector2f(hitboxPosition.x * windowDimensions.x / 1920.f, hitboxPosition.y* windowDimensions.y / 1080.f));
	hitbox.setSize(hitboxSize);
	hitbox.setScale(sf::Vector2f(hitbox.getScale().x * windowDimensions.x / 1920.f, hitbox.getScale().y * windowDimensions.y / 1080.f));

	hitbox.setOutlineColor(sf::Color::White);
	hitbox.setOutlineThickness(-1);
	hitbox.setFillColor(sf::Color::Transparent);
}

bool Bouton::Update(float textScale, sf::Vector2f windowDimensions, sf::Vector2f mousePosition)
{
	boutonText->Update(textScale,sf::Vector2f(hitbox.getPosition().x+(hitbox.getSize().x*textPosistionRatio.x), 
		hitbox.getPosition().y + (hitbox.getSize().y * textPosistionRatio.y)));
	hitbox.setPosition(sf::Vector2f(hitbox.getPosition().x*windowDimensions.x/1920.f, hitbox.getPosition().y * windowDimensions.y / 1080.f));
	hitbox.setScale(sf::Vector2f(hitbox.getScale().x * windowDimensions.x / 1920.f, hitbox.getScale().y * windowDimensions.y / 1080.f));
	return(hitbox.getGlobalBounds().contains(mousePosition));
}



void Bouton::Draw(sf::RenderWindow* window) const
{
	window->draw(hitbox);
	boutonText->Draw(window);
}
