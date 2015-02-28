#pragma once

class Area : public cocos2d::Node
{
public:
	Area();
	virtual ~Area();
	virtual bool init();
	virtual	void update(float dTime);

	CREATE_FUNC(Area);
private:

private:

};