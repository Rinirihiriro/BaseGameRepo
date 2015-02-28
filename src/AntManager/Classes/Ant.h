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

public:
	enum MoveDirection
	{
		MD_NONE,
		MD_UP,
		MD_UP_LEFT,
		MD_LEFT,
		MD_UP_RIGHT,
		MD_RIGHT,
		MD_MAX,
	};

private:
	void			move(float dTime);
	void			makeDirVector();
	void			makeSprite();
	void			initProbability();
	bool			isNoWayToGo();
	int				findBestDir();

	void decideNextDirection(float dTime);

private:
	int									m_MoveCount;
	std::array<cocos2d::Vec2, MD_MAX>	m_DirVector;
	std::array<int, MD_MAX>				m_DirProbability;
	cocos2d::Sprite*					m_Sprite;
};