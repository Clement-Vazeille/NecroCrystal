#pragma once
#include<string>
#include"MapData.h"

class MapLoader
{
public:
	static void Load(std::string fileName,MapData& mapData);
};

