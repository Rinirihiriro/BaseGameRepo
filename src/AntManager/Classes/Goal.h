#pragma once
#include "Area.h"
class Ant;
class Goal : public Area
{
public:
	Goal();
	virtual ~Goal();
	virtual bool	init();
	virtual void	update(float dTime);
	virtual bool	isContain(const cocos2d::Point& point) const ;
	virtual void	effectOnUnit(Unit* u);
	void			arrivedGoal(cocos2d::Node* ref, Ant* ant);
	void			initWithRect(cocos2d::Rect rect);
	CREATE_FUNC(Goal);

private:

private:
	cocos2d::Rect	m_Rect;
};