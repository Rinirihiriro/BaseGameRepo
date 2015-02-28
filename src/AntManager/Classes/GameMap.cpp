#include "Pch.h"
#include "GameMap.h"
#include "DataManager.h"
#include "MapModel.h"
#include "MapTile.h"
#include "Define.h"
#include "Ant.h"
#include "Goal.h"

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
	addListener();
	scheduleUpdate();
	return true;
}

void GameMap::initWithModel(MapModel* mapModel)
{
	m_MapModel = mapModel;
	makeTiles();
	makeAreas();
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

void GameMap::makeAreas()
{
	auto goal1 = Goal::create();
	goal1->initWithRect(Rect(16 * 3, 640 - 16 * 2, 16 * 4, 16 * 2));
	addChild(goal1);
	m_Areas.push_back(goal1);

	auto goal2 = Goal::create();
	goal2->initWithRect(Rect(16 * 13, 640 - 16 * 2, 16 * 4, 16 * 2));
	addChild(goal2);
	m_Areas.push_back(goal2);

	auto goal3 = Goal::create();
	goal3->initWithRect(Rect(16 * 23, 640 - 16 * 2, 16 * 4, 16 * 2));
	addChild(goal3);
	m_Areas.push_back(goal3);

}

void GameMap::addListener()
{
	cocos2d::EventListenerCustom* listener = cocos2d::EventListenerCustom::create(
		"add Ant", CC_CALLBACK_0(GameMap::addAnt, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameMap::addAnt()
{
	auto ant = Ant::create();
	int leftIdx = 0;
	int rightIdx = 0;
	m_MapModel->findFirstGate(&leftIdx, &rightIdx);
	float leftPos = leftIdx * TILE_SIZE_WIDTH;
	float rightPos = rightIdx * TILE_SIZE_WIDTH;
	float setPosX = leftPos + rand() % (int) ( rightPos - leftPos );

	ant->setPosition(Point(setPosX, 0));
	addChild(ant);
	m_Ants.push_back(ant);
}

void GameMap::checkArea()
{
	for(auto ant : m_Ants)
	{
		for(auto area : m_Areas)
		{
			if(area->isContain(ant->getPosition()))
			{
				area->effectOnUnit(ant);
			}
		}
	}
}

void GameMap::update(float dTime)
{
	checkArea();
}
