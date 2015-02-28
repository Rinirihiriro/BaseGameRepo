#pragma once

class Unit;

class Area : public cocos2d::Node
{
public:
	Area(const float activeTime = 1, const float inactiveTime = 0);
	virtual ~Area();
	virtual bool init();
	virtual	void update(float dTime);

	CREATE_FUNC(Area);

	virtual bool isContain(const cocos2d::Point& point) const = 0;
	virtual void effectOnUnit(Unit* u) = 0;

	void Active();
	void Inactive();

private:

private:
	bool m_Active;
	float m_ActiveTime;
	float m_InactiveTime;
};