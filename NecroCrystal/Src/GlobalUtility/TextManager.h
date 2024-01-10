#pragma once
#include <string>
#include "Sentence.h"

//Class used to create a text
class TextManager
{
protected:
	sf::Texture texture;
public:
	TextManager();

	void Initialize();
	Sentence* MakeSentence(std::string& text);
};

