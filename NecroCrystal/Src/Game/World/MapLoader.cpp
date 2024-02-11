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

				if (variable == "tileSheet")         //un switch avec un Enum, ce serait plus rapide à executer mais plus long à faire
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
				else if (variable == "walls") //hitbox reader
				{
					int hitboxNumber = std::stoi(value);
					mapData.hitboxNumber = hitboxNumber;
					mapData.wallHitboxPositions = new sf::Vector2f[hitboxNumber];
					mapData.wallHitboxSizes = new sf::Vector2f[hitboxNumber];
					for (int i = 0; i < hitboxNumber; i++)
					{
						int start = 0;            //a line is xposition,yposition,width,height
						int end = 0;			  //values unity is tiles
						std::getline(file, line); 

						end = line.find(',', start);
						mapData.wallHitboxPositions[i].x = std::stoi(line.substr(start, end - start));
						start = end + 1;
						end = line.find(',', start);
						mapData.wallHitboxPositions[i].y = std::stoi(line.substr(start, end - start));
						start = end + 1;
						end = line.find(',', start);
						mapData.wallHitboxSizes[i].x = std::stoi(line.substr(start, end - start));
						start = end + 1;
						end = line.find(',', start);
						mapData.wallHitboxSizes[i].y = std::stoi(line.substr(start, end - start));
					}
				}
				else if (variable == "spawn")
				{
					int virgIndex = value.find(',');
					mapData.necroSpawn.x = std::stoi(value.substr(0, virgIndex)) * mapData.tileWidth*mapData.scaleX;
					mapData.necroSpawn.y = std::stoi(value.substr(virgIndex + 1, value.length() - virgIndex - 1)) * mapData.tileHeight * mapData.scaleY;
				}
				else if (variable == "enemies")
				{
					int enemyNumber = std::stoi(value);
					mapData.enemyNumber = enemyNumber;
					mapData.enemyTypes = new int[enemyNumber];
					mapData.enemyPositions = new sf::Vector2f[enemyNumber];
					for (int i = 0; i < enemyNumber; i++)
					{
						int start = 0;            //a line is xposition,yposition,width,height
						int end = 0;			  //values unity is tiles
						std::getline(file, line);

						end = line.find(',', start);
						mapData.enemyPositions[i].x = std::stoi(line.substr(start, end - start)) * mapData.tileWidth * mapData.scaleX;
						start = end + 1;
						end = line.find(',', start);
						mapData.enemyPositions[i].y = std::stoi(line.substr(start, end - start)) * mapData.tileHeight * mapData.scaleY;
						start = end + 1;
						end = line.find(',', start);
						mapData.enemyTypes[i] = std::stoi(line.substr(start, end - start));
					}
				}
				else if (variable == "waves")
				{
					int waveNumber = std::stoi(value);
					mapData.waveNumber = waveNumber;
					mapData.waveEnemyIndex = new int[waveNumber];
					std::getline(file, line);
					int start = 0;
					int end = 0;
					for (int i = 0; i < waveNumber; i++)
					{
						
						end = line.find(',', start);
						mapData.waveEnemyIndex[i] = std::stoi(line.substr(start, end - start));

						start = end + 1;
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
