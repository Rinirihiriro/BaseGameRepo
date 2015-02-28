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
	return true;
}

void GameMap::initWithModel(MapModel* mapModel)
{
	m_MapModel = mapModel;
	makeTiles();
}

void GameMap::makeTiles()
{
	int width = m_MapModel->getWidth();
	int height = m_MapModel->getHeight();
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
			m_Tiles[checkIdx]->initTile(m_MapModel->getData(checkIdx));
			m_Tiles[checkIdx]->setPosition(setPos);
			addChild(m_Tiles[checkIdx]);
		}
	}
}

