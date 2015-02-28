#include "Pch.h"
#include "MachineModel.h"
#include "GameManager.h"
#include "DataManager.h"
#include "PlayerModel.h"
#include "MapModel.h"

USING_NS_CC;

MachineModel::MachineModel()
	:m_ExchangeRate(0.f), m_AvailableAntsCount(0)
{
	m_MapModel = new MapModel();
}

MachineModel::~MachineModel()
{
}

bool MachineModel::sellAnts(int numOfAnts)
{
	if(m_AvailableAntsCount < numOfAnts)
		return false;

	PlayerModel* player = GET_GAME_MANAGER()->getPlayer();
	int curMoney = player->getMoney();
	int cost = numOfAnts * m_ExchangeRate;
	
	player->setMoney(curMoney + cost);
	m_AvailableAntsCount -= numOfAnts;

	return true;
}
bool MachineModel::buyAnts(int numOfAnts)
{
	PlayerModel* player = GET_GAME_MANAGER()->getPlayer();
	int curMoney = player->getMoney();
	int cost = numOfAnts * m_ExchangeRate;

	if(curMoney < cost)
		return false;

	m_AvailableAntsCount += numOfAnts;
	player->setMoney(curMoney - cost);
	return true;
}

void MachineModel::initMachine(int machineType)
{
	char buffer[128] = {0, };
	sprintf(buffer, "map0%d.json", machineType);
	m_MapFilePath = buffer;
	initFromFile(m_MapFilePath);
}

void MachineModel::initFromFile(const std::string& filePath)
{
	std::string str = GET_DATA_MANAGER()->readFromFile(filePath);
	Json::Value root = GET_DATA_MANAGER()->toJsonFromString(str);
	
	m_ExchangeRate = root["exchangeRate"].asInt();
	m_MapModel->initFromJson(root["tile"]);
}

MapModel* MachineModel::getMapModel()
{
	return m_MapModel;
}
