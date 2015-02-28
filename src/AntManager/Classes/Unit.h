#pragma once
#include "cocos2d.h"

class Unit :public cocos2d::Node
{
public:
	virtual ~Unit() = 0;

	void updatePosition(const float dTime);

protected:
	cocos2d::Vec2 m_Velocity;

};