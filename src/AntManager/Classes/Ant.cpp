#include "Pch.h"
#include "Ant.h"
#include "DataManager.h"
#include "GameManager.h"
#include "MachineModel.h"
#include "MapModel.h"
#include "Define.h"

USING_NS_CC;

Ant::Ant()
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
	makeSprite();
	scheduleUpdate();
	schedule(schedule_selector(Ant::decideNextDirection), 0.5f);
	m_Velocity = Vec2::UNIT_Y * ( rand() % 10 + 20 );
	return true;
}

void Ant::update(float dTime)
{
	updatePosition(dTime);
	wallProcess();
}


void Ant::decideNextDirection(float dTime)
{
	bool directions[9] = { false, };
	// 6 7 8
	// 3 4 5
	// 0 1 2

	auto pos = getPosition();
	MapModel* mapModel = GET_GAME_MANAGER()->getMachine()->getMapModel();

	int xIdx = pos.x / TILE_SIZE_WIDTH;
	int yIdx = pos.y / TILE_SIZE_HEIGHT;

	for (int y = 1; y < 3; ++y) {
		for (int x = 0; x < 3; ++x) {
			if (x == 1 && y == 1) continue;
			if (x != 1 && y != 1) continue; // 좌우상하만 고려하기 위해

			int xx = xIdx + x - 1;
			int yy = yIdx + y - 1;
			if (xx < 0 || xx >= mapModel->getWidth()
				|| yy < 0 || yy >= mapModel->getHeight())
				continue;

			int checkIdx = xx + yy * mapModel->getWidth();
			directions[x+y*3] = mapModel->getData(checkIdx) == 0;
		}
	}

	std::vector<int> pocket;
	for (int i = 0; i < _countof(directions); ++i)
	{
		if (directions[i])
			pocket.push_back(i);
	}

	// 사방이 벽
	if (pocket.empty())
		return;

	int targetDir = pocket[rand() % pocket.size()];

	Vec2 target((targetDir % 3 - 1), (targetDir / 3 - 1));
	target.normalize();
	float amount = target.cross(m_Velocity.getNormalized());
	m_Velocity = m_Velocity.rotateByAngle(Vec2::ZERO, -0.5f * amount);

	m_Sprite->runAction(
		RotateTo::create(dTime, 90.f - CC_RADIANS_TO_DEGREES(m_Velocity.getAngle()))
		);
}

void Ant::makeSprite()
{
	m_Sprite = Sprite::create("ant_black.png");
	addChild(m_Sprite);
}

void Ant::wallProcess()
{
	auto pos = getPosition();

	// 맵 밖으로 못 나가게
	if (pos.x < 0)
		pos.x = 0;
	else if (pos.x > 480)
		pos.x = 480;
	if (pos.y < 0)
		pos.y = 0;
	else if (pos.y > 640)
		pos.y = 640;

	setPosition(pos);

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
				pos.x = dx - TILE_SIZE_WIDTH * 0.6;
			else
				pos.x = dx + TILE_SIZE_WIDTH * 0.6;
		}
		else
		{
			if (dy > pos.y)
				pos.y = dy - TILE_SIZE_WIDTH * 0.6;
			else
				pos.y = dy + TILE_SIZE_WIDTH * 0.6;
		}
		setPosition(pos);
	}
}
