#include "MapLoader.h"
#include<fstream>
#include<iostream>


void MapLoader::Load(std::string fileName,MapData& mapData)
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
				std::string variable = line.substr(0, separatorIndex);
				std::string value = line.substr(separatorIndex + 1, line.length() - separatorIndex);

				if (variable == "tileSheet")         //un switch avec un Enum, ce serait plus rapide � executer mais plus long � faire
				{
					mapData.tileSheet = value;
				}
				else if (variable == "name")
				{
					mapData.name = value;
				}
				else if (variable == "tileWidth")
				{
					mapData.tileWidth = std::stoi(value);
				}
				else if (variable == "tileHeight")
				{
					mapData.tileHeight = std::stoi(value);
				}
				else if (variable == "scaleX")
				{
					mapData.scaleX = std::stof(value);
				}
				else if (variable == "scaleY")
				{
					mapData.scaleY = std::stof(value);
				}
				else if (variable == "mapHeight")
				{
					mapData.mapHeight = std::stoi(value);
				}
				else if (variable == "mapWidth")
				{
					mapData.mapWidth = std::stoi(value);
				}
				else if (variable == "tiles")
				{
					mapData.tilesNumber = mapData.mapHeight * mapData.mapWidth;
					mapData.tiles = new int*[mapData.mapHeight];
					for(int y=0;y<mapData.mapHeight;y++)
					{
						int start = 0;
						int end = 0;
						mapData.tiles[y] = new int[mapData.mapWidth];
						std::getline(file, line);
						for (int x = 0; x < mapData.mapWidth; x++)
						{
							end = line.find(',', start);
							mapData.tiles[y][x] = std::stoi(line.substr(start, end - start));

							start = end + 1;
						}

					}
				}
			}

		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open" << fileName << std::endl;
	}
}
