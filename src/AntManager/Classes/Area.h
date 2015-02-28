#pragma once

class Unit;

class Area : public cocos2d::Node
{
public:
	Area();
	virtual ~Area();
	virtual bool init();
	virtual	void update(float dTime);

	CREATE_FUNC(Area);

	virtual bool isContain(const cocos2d::Point& point) const;

private:
	virtual void effectOnUnit(Unit* u) = 0;

private:
	bool m_Active;
	float m_ActiveTime;
	float m_InactiveTime;
};