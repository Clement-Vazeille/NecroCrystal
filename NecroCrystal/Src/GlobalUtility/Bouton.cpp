#include "Bouton.h"

Bouton::Bouton() :
	boutonText(nullptr), scale(2.f), hasClickBeenUnpressed(false)
{
}

Bouton::~Bouton()
{
	delete boutonText;
}

void Bouton::Initialise(Sentence* sentence, sf::Vector2f hitboxPosition, sf::Vector2f hitboxSize, sf::Vector2i windowDimensions, sf::Vector2f textRatio)
{
	boutonText = sentence; // on suppose que sentence est déjà initialisé
	hitbox.setPosition(sf::Vector2f(hitboxPosition.x * windowDimensions.x / 1920.f, hitboxPosition.y* windowDimensions.y / 1080.f));
	hitbox.setSize(hitboxSize);
	hitbox.setScale(sf::Vector2f(hitbox.getScale().x * windowDimensions.x / 1920.f, hitbox.getScale().y * windowDimensions.y / 1080.f));

	hitbox.setOutlineColor(sf::Color::White);
	hitbox.setOutlineThickness(-3);
	hitbox.setFillColor(sf::Color::Transparent);

	textPosistionRatio = textRatio; //Projet, on supprime le textRatio et on prend juste le contour du texte
}

bool Bouton::Update(float textScale, sf::Vector2i windowDimensions, sf::Vector2f mousePosition)
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		hasClickBeenUnpressed = true;

	boutonText->Update(textScale,sf::Vector2f(hitbox.getPosition().x+(hitbox.getSize().x*textPosistionRatio.x), 
		hitbox.getPosition().y + (hitbox.getSize().y * (1.f-textPosistionRatio.y))));
	hitbox.setPosition(sf::Vector2f(hitbox.getPosition().x*windowDimensions.x/1920.f, hitbox.getPosition().y * windowDimensions.y / 1080.f));
	hitbox.setScale(sf::Vector2f(hitbox.getScale().x * windowDimensions.x / 1920.f, hitbox.getScale().y * windowDimensions.y / 1080.f));

	return(hasClickBeenUnpressed &&
		hitbox.getGlobalBounds().contains(mousePosition) && 
		sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
}

void Bouton::Reset(void)
{
	hasClickBeenUnpressed = false;
}



void Bouton::Draw(sf::RenderWindow* window) const
{
	window->draw(hitbox);
	boutonText->Draw(window);
}
