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
					std::cout << "Map file is not valid";
					break;
				}
			}


			if (isMapValid)
			{
				std::cout << line << std::endl;
			}

		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open" << fileName << std::endl;
	}
}
