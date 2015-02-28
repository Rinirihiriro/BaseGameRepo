#include "Pch.h"
#include "GameMap.h"
#include "DataManager.h"
#include "MapModel.h"
#include "MapTile.h"
#include "Define.h"

USING_NS_CC;

GameMap::GameMap()
{
}

GameMap::~GameMap()
{
}

bool GameMap::init()
{
	if(!Node::init())
	{
		return false;
	}
	makeTiles();
	return true;
}

void GameMap::makeTiles()
{
	MapModel* mapModel = GET_DATA_MANAGER()->getMapModel();
	int width = mapModel->getWidth();
	int height = mapModel->getHeight();
	int checkIdx = 0;
	Point setPos;
	m_Tiles.resize(width*height);
	for(int xIdx = 0; xIdx < width; ++xIdx)
	{
		for(int yIdx = 0; yIdx < height; ++yIdx)
		{
			checkIdx = xIdx + yIdx * width;
			setPos.x = xIdx * TILE_SIZE_WIDTH;
			setPos.y = yIdx * TILE_SIZE_HEIGHT;
			m_Tiles[checkIdx] = MapTile::create();
			m_Tiles[checkIdx]->initTile(mapModel->getData(checkIdx));
			m_Tiles[checkIdx]->setPosition(setPos);
			addChild(m_Tiles[checkIdx]);
		}
	}
}
