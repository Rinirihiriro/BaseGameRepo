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


void MapModel::initFromJson(const Json::Value& value)
{
	int checkIdx = 0;
	int reversedIdx = 0;
	
	m_Width = value["width"].asInt();
	m_Height = value["height"].asInt();
	m_MapData.resize(m_Width * m_Height);
	for(int xIdx = 0; xIdx < m_Width; ++xIdx)
	{
		for(int yIdx = 0; yIdx < m_Height; ++yIdx)
		{
			checkIdx = xIdx + yIdx * m_Width;
			reversedIdx = xIdx + ( m_Height - yIdx - 1 ) * m_Width;
			m_MapData[checkIdx] = value["tiles"][reversedIdx].asInt();
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

bool MapModel::findFirstGate(int* leftIdx, int* rightIdx)
{
	int checkIdx = 0;
	bool isFirst = true;
	bool isContinuosOpen = false;
	for(int xIdx = 0; xIdx < m_Width; ++xIdx)
	{
		checkIdx = xIdx;
		if(isFirst && m_MapData[checkIdx] == 0)
		{
			isFirst = false;
			isContinuosOpen = true;
			*leftIdx = xIdx;
		}
		else if(isContinuosOpen && m_MapData[checkIdx] != 0)
		{
			*rightIdx = xIdx;
			break;
		}
	}
	return true;
}
