#include "TextManager.h"
#include <iostream>

TextManager::TextManager()
{
}

void TextManager::Initialize()
{
	if (texture.loadFromFile("Assets/Fonts/fontPerso.png"))
	{
		std::cout << "Font texture loaded successfully" << std::endl;
	}
	else
		std::cout << "Font texture failed to load" << std::endl;
}

Sentence* TextManager::MakeSentence(std::string& text)
{
	Sentence* sentence = new Sentence(); 
	sentence->Initialise(text, texture);
	return sentence;
}
