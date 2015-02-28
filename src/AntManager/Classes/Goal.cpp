#include "Pch.h"
#include "Goal.h"
#include "Type.h"
#include "Unit.h"
#include "Ant.h"

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
	auto ant = static_cast<Ant*>( u );
	Point srcPos = u->getPosition();
	Point dstPos = m_Rect.origin;
	dstPos.x += m_Rect.size.width / 2;
	dstPos.y += m_Rect.size.height;
	ant->unscheduleUpdate();
	auto move = MoveTo::create(1.f, dstPos);
	auto spin = RotateTo::create(1.f, 360);
	auto spawn = Spawn::create(move, spin, NULL);
	auto endCallback = CallFuncN::create(CC_CALLBACK_1(Goal::arrivedGoal, this, ant));
	auto sequence = Sequence::create(spawn, endCallback, nullptr);
	u->runAction(sequence);
}

void Goal::update(float dTime)
{
}

bool Goal::isContain(const cocos2d::Point& point) const
{
	return m_Rect.containsPoint(point);
}

void Goal::arrivedGoal(cocos2d::Node* ref, Ant* ant)
{
	//ant->removeFromParent();
}
