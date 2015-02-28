#include "Pch.h"
#include "Ant.h"
#include "DataManager.h"
#include "MapModel.h"
#include "Define.h"

USING_NS_CC;

Ant::Ant()
	:m_MoveCount(0)
{

}

Ant::~Ant()
{

}

bool Ant::init()
{
	if(!Unit::init())
	{
		return false;
	}
	makeDirVector();
	makeSprite();
	scheduleUpdate();
	initProbability();
	return true;
}

void Ant::update(float dTime)
{
	move(dTime);
}

void Ant::move(float dTime)
{
	if(m_MoveCount++ > 5)
	{
		m_MoveCount = 0;
		MapModel* mapModel = GET_DATA_MANAGER()->getMapModel();
		Rect fieldRect(0, 0, 480, 640);
		int moveDirection = findBestDir();
		Vec2 moveVec = m_DirVector[moveDirection] * dTime * 300;
		Point nextPos = getPosition() + moveVec;
		int xIdx = nextPos.x / TILE_SIZE_WIDTH;
		int yIdx = nextPos.y / TILE_SIZE_HEIGHT;
		int checkIdx = xIdx + yIdx * mapModel->getWidth();
		while(!fieldRect.containsPoint(nextPos) || mapModel->getData(checkIdx))
		{
			m_DirProbability[moveDirection]--;
			moveDirection = rand() % MD_MAX;
			moveVec = m_DirVector[moveDirection] * dTime * 300;
			nextPos = getPosition() + moveVec;
			xIdx = nextPos.x / TILE_SIZE_WIDTH;
			yIdx = nextPos.y / TILE_SIZE_HEIGHT;
			checkIdx = xIdx + yIdx * mapModel->getWidth();
			if(isNoWayToGo())
			{
				removeFromParent();
				return;
			}
		}
		initProbability();
		setPosition(nextPos);
	}
	return;
}

void Ant::makeDirVector()
{
	m_DirVector[MD_UP] = Vec2(0, 1);
	m_DirVector[MD_UP_LEFT] = Vec2(-1, 1);
	m_DirVector[MD_UP_RIGHT] = Vec2(1, 1);
	m_DirVector[MD_LEFT] = Vec2(-1, 0);
	m_DirVector[MD_RIGHT] = Vec2(1, 0);

	
}

void Ant::makeSprite()
{
	m_Sprite = Sprite::create("ant_black.png");
	addChild(m_Sprite);
}

void Ant::initProbability()
{
	m_DirProbability[MD_NONE] = 0;
	m_DirProbability[MD_LEFT] = 10;
	m_DirProbability[MD_RIGHT] = 10;
	m_DirProbability[MD_UP] = 11;
	m_DirProbability[MD_UP_LEFT] = 11;
	m_DirProbability[MD_UP_RIGHT] = 11;
}

bool Ant::isNoWayToGo()
{
	bool ret = true;
	for(int i = 0; i < MD_MAX; ++i)
	{
		if(m_DirProbability[i] > 0)
		{
			ret = false;
		}
	}
	return ret;
}

int Ant::findBestDir()
{
	std::vector<int> bestDirs;
	int bestProbability = 0;
	int bestDir = MD_NONE;
	int checkProbability = 0;
	for(int dir = 0; dir < MD_MAX; ++dir)
	{
		checkProbability = m_DirProbability[dir];
		if( checkProbability > bestProbability)
		{
			bestProbability = checkProbability;
			bestDir = dir;
			bestDirs.clear();
			bestDirs.push_back(dir);
		}
		else if(checkProbability == bestProbability)
		{
			bestDirs.push_back(dir);
		}
	}
	
	return bestDirs[rand() % bestDirs.size()];
}
