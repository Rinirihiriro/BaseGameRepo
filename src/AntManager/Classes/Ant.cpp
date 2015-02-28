#include "Pch.h"
#include "Ant.h"
#include "DataManager.h"
#include "GameManager.h"
#include "MachineModel.h"
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
	schedule(schedule_selector(Ant::decideNextDirection), 0.5f);
//	initProbability();
	m_Velocity = Vec2::UNIT_Y * (rand() % 10 + 20);
	return true;
}

void Ant::update(float dTime)
{
	updatePosition(dTime);

	auto pos = getPosition();
	MapModel* mapModel = GET_GAME_MANAGER()->getMachine()->getMapModel();
	int xIdx = pos.x / TILE_SIZE_WIDTH;
	int yIdx = pos.y / TILE_SIZE_HEIGHT;
	int checkIdx = xIdx + yIdx * mapModel->getWidth();
	if (mapModel->getData(checkIdx) != 0)
	{
		float dx = (xIdx + 0.5f) * TILE_SIZE_WIDTH;
		float dy = (yIdx + 0.5f) * TILE_SIZE_HEIGHT;
		if (abs(dx - pos.x) > abs(dy - pos.y))
		{
			if (dx > pos.x)
				pos.x = dx - TILE_SIZE_WIDTH / 2;
			else
				pos.x = dx + TILE_SIZE_WIDTH / 2;
		}
		else
		{
			if (dy > pos.y)
				pos.y = dy - TILE_SIZE_WIDTH / 2;
			else
				pos.y = dy + TILE_SIZE_WIDTH / 2;
		}
		setPosition(pos);

		m_Velocity = m_Velocity.rotateByAngle(Vec2::ZERO, (rand()%200-100)*0.01f);
		m_Sprite->runAction(
			RotateTo::create(dTime, 90.f - CC_RADIANS_TO_DEGREES(m_Velocity.getAngle()))
			);
	}

//	decideNextDirection(dTime);
	// move(dTime);
}

void Ant::decideNextDirection(float dTime)
{
	float angle = CC_RADIANS_TO_DEGREES(m_Velocity.getAngle());
	float dice = (rand() % 1800) * 0.1f;
	float delta = angle - dice;

	if (abs(delta) < 1.f)
	{
		// 전진
		return;
	}
	else if (delta < 0)
	{
		// 좌회전
//		m_Velocity = m_Velocity.rotateByAngle(Vec2::ZERO, 10.f * dTime);
		m_Velocity = m_Velocity.rotateByAngle(Vec2::ZERO, 0.2f);
	}
	else
	{
		// 우회전
//		m_Velocity = m_Velocity.rotateByAngle(Vec2::ZERO, -10.f * dTime);
		m_Velocity = m_Velocity.rotateByAngle(Vec2::ZERO, -0.2f);
	}
	m_Sprite->runAction(
		RotateTo::create(dTime, 90.f - CC_RADIANS_TO_DEGREES(m_Velocity.getAngle()))
		);
}

void Ant::move(float dTime)
{
	if(m_MoveCount++ > 5)
	{
		m_MoveCount = 0;
		MapModel* mapModel = GET_GAME_MANAGER()->getMachine()->getMapModel();
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
