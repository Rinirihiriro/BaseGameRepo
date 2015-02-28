#pragma once

class PlayerModel : public cocos2d::Object
{
public:
	PlayerModel();
	virtual ~PlayerModel();
	virtual bool init();

private:
	CC_SYNTHESIZE(int, m_Money, Money);
};