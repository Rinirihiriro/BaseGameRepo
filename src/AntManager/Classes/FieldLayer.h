#pragma once

//���� ������ �������� Field�� Layer
class GameMap;
class FieldLayer : public cocos2d::Layer
{
public:
	FieldLayer();
	virtual ~FieldLayer();
	virtual bool	init();
	virtual void	update(float dTime);

	CREATE_FUNC(FieldLayer);
private:

private:
	float			m_AccTime;
	GameMap*		m_GameMap;
};