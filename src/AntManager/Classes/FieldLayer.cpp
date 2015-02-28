#include "Pch.h"
#include "FieldLayer.h"
#include "GameManager.h"
#include "MachineModel.h"
#include "GameMap.h"
#include "Ant.h"

USING_NS_CC;

FieldLayer::FieldLayer()
	:m_GameMap(nullptr)
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
}

void FieldLayer::addListener()
{
}

