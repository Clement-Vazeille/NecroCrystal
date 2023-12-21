#include "MapLoader.h"
#include<fstream>
#include<iostream>


void MapLoader::Load(std::string fileName)
{
	std::string line;
	std::ifstream file(fileName);

	bool isMapValid = false;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			if (!isMapValid)
			{
				if (line == "[Map]")
				{
					isMapValid = true;
					continue; //go to the next while loop iteration
				}
				else
				{
					std::cout << "Map file " << fileName << " is not valid";
					break;
				}
			}


			if (isMapValid)
			{
				int separatorIndex = line.find('='); //the separator is the character = 
				std::string variableName = line.substr(0, separatorIndex);
				std::string value = line.substr(separatorIndex + 1, line.length() - separatorIndex);

				std::cout << line << std::endl;
				break;
			}

		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open" << fileName << std::endl;
	}
}
