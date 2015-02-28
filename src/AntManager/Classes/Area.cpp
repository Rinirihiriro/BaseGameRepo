#include "Pch.h"
#include "Area.h"

USING_NS_CC;

Area::Area(const float activeTime, const float inactiveTime)
	:m_Active(false), m_ActiveTime(activeTime), m_InactiveTime(inactiveTime)
{

}

Area::~Area()
{

}

bool Area::init()
{
	if(!Node::init())
	{
		return false;
	}

	if (m_ActiveTime > 0 && m_InactiveTime > 0)
	{
		runAction(RepeatForever::create(
			Sequence::create(
			DelayTime::create(m_InactiveTime)
			, CallFunc::create(CC_CALLBACK_0(Area::Active, this))
			, DelayTime::create(m_ActiveTime)
			, CallFunc::create(CC_CALLBACK_0(Area::Inactive, this))
			, nullptr)));
	}
	else if (m_ActiveTime > 0)
	{
		m_Active = true;
	}

	return true;
}

void Area::update(float dTime)
{
}

void Area::Active()
{
	m_Active = true;
}

void Area::Inactive()
{
	m_Active = false;
}
