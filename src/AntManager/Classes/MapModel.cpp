#include "Pch.h"
#include "MapModel.h"
#include "DataManager.h"

MapModel::MapModel()
	:m_Width(0), m_Height(0)
{

}

MapModel::~MapModel()
{
}

void MapModel::initFromFile(const std::string& filePath)
{
	std::string str = GET_DATA_MANAGER()->readFromFile(filePath);
	fromJson(GET_DATA_MANAGER()->toJsonFromString(str));
}

void MapModel::fromJson(const Json::Value& value)
{
	int checkIdx = 0;
	int reversedIdx = 0;
	Json::Value tileData = value["tile"];
	m_Width = tileData["width"].asInt();
	m_Height = tileData["height"].asInt();
	m_MapData.resize(m_Width * m_Height);

	for(int xIdx = 0; xIdx < m_Width; ++xIdx)
	{
		for(int yIdx = 0; yIdx < m_Height; ++yIdx)
		{
			checkIdx = xIdx + yIdx * m_Width;
			reversedIdx = xIdx + ( m_Height - yIdx - 1 ) * m_Width;
			m_MapData[checkIdx] = tileData["tiles"][reversedIdx].asInt();
		}
	}
}

int MapModel::getData(int idx)
{
	int returnType = -1;
	if(idx >= 0 && idx < m_MapData.size())
	{
		returnType = m_MapData[idx];
	}
	return returnType;
}
