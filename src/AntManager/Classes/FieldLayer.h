#pragma once

//���� ������ �������� Field�� Layer
class GameMap;
class FieldLayer : public cocos2d::Layer
{
public:
	FieldLayer();
	virtual ~FieldLayer();
	virtual bool	init();

	CREATE_FUNC(FieldLayer);
private:

private:
	GameMap*		m_GameMap;
};