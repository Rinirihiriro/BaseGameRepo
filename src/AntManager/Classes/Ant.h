#pragma once
#include "Unit.h"

class Ant : public Unit
{
public:
	Ant();
	virtual ~Ant();
	virtual bool	init();
	virtual void	update(float dTime);

	CREATE_FUNC(Ant);

private:
	void	makeSprite();
	void	decideNextDirection(float dTime);
	void	wallProcess();

private:
	cocos2d::Sprite*	m_Sprite;
};