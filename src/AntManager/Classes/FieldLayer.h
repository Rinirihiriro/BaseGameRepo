#pragma once

//실제 게임이 벌어지는 Field의 Layer
class GameMap;
class MachineModel;
class FieldLayer : public cocos2d::Layer
{
public:
	FieldLayer();
	virtual ~FieldLayer();
	virtual bool	init();
	virtual void	update(float dTime);
	void			initWithModel(MachineModel* machineModel);

	CREATE_FUNC(FieldLayer);
private:

private:
	float			m_AccTime;
	GameMap*		m_GameMap;
	MachineModel*	m_MachineModel;
};