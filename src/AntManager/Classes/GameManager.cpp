#include "pch.h"
#include "GameManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "MachineModel.h"
#include "PlayerModel.h"
#include "Macro.h"
#include "Type.h"

USING_NS_CC;

GameManager* GameManager::m_Instance = nullptr;

GameManager::GameManager()
{
	m_Machine = new MachineModel();
	m_Player = new PlayerModel();
}

GameManager::~GameManager()
{
}

GameManager* GameManager::getInstance()
{
	if(m_Instance == nullptr)
	{
		m_Instance = new GameManager();
	}
	return m_Instance;
}

void GameManager::releaseInstance()
{
	SAFE_DELETE(m_Instance);
}


void GameManager::changeScene(int sceneType)
{
	Scene* scene = nullptr;
	switch(sceneType)
	{
		case SceneType::ST_TITLE:
			scene = TitleScene::createScene();
			break;
		case SceneType::ST_GAME:
			scene = GameScene::createScene();
			break;
		default:
			break;
	}

	if(scene != nullptr)
	{
		Director::getInstance()->replaceScene(scene);
	}
}

PlayerModel* GameManager::getPlayer()
{
	return m_Player;
}

MachineModel* GameManager::getMachine()
{
	return m_Machine;
}

void GameManager::startGame(int machineType)
{
	m_Machine->initMachine(machineType);
	changeScene(SceneType::ST_GAME);
}
