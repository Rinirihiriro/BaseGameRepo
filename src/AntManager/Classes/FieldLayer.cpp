#include "Pch.h"
#include "FieldLayer.h"
#include "GameManager.h"
#include "MachineModel.h"
#include "GameMap.h"
#include "Ant.h"

USING_NS_CC;

FieldLayer::FieldLayer()
	:m_GameMap(nullptr), m_AccTime(0.f)
{
}

FieldLayer::~FieldLayer()
{
}

bool FieldLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	
	m_GameMap = GameMap::create();
	m_GameMap->initWithModel(GET_GAME_MANAGER()->getMachine()->getMapModel());
	addChild(m_GameMap);
	scheduleUpdate();
	return true;
}


void FieldLayer::update(float dTime)
{
	m_AccTime += dTime;
	if(m_AccTime > 1.f)
	{
		m_AccTime = 0;
		auto newAnt = Ant::create();
		float posX = 480/2 + (rand() % 40) - 40;
		newAnt->setPosition(Point(posX, 0.f));
		addChild(newAnt);
	}
}

