#include "Pch.h"
#include "Goal.h"
#include "Type.h"

USING_NS_CC;

Goal::Goal()
{

}

Goal::~Goal()
{

}

bool Goal::init()
{
	if(!Area::init())
	{
		return false;
	}
	auto sprite = Sprite::create("Goal.png");
	addChild(sprite);
	return true;
}


void Goal::initWithRect(cocos2d::Rect rect)
{
	m_Rect = rect;
	Point setPos(m_Rect.origin.x + m_Rect.size.width / 2, m_Rect.origin.y + m_Rect.size.height / 2);
	setPosition(setPos);
	setAnchorPoint(Vec2::ZERO);
}


void Goal::effectOnUnit(Unit* u)
{

}

void Goal::update(float dTime)
{
}

bool Goal::isContain(const cocos2d::Point& point) const
{
	return m_Rect.containsPoint(point);
}
