#pragma once
#define GET_GAME_MANAGER GameManager::getInstance

class PlayerModel;
class MachineModel;
class GameManager : public cocos2d::Object
{
public:
	static GameManager*	getInstance();
	void				releaseInstance();
	void				changeScene(int sceneType);
	void				startGame(int machineType);
	PlayerModel*		getPlayer();
	MachineModel*		getMachine();

private:
	GameManager();
	virtual ~GameManager();

private:
	static GameManager*	m_Instance;
	PlayerModel*		m_Player;
	MachineModel*		m_Machine;
};

