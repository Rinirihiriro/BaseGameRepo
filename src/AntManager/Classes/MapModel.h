#pragma once
#include "json.h"

class MapModel : public cocos2d::Object
{
public:
	MapModel();
	virtual	~MapModel();
	void	initFromJson(const Json::Value& value);
	int		getData(int idx);
	bool	findFirstGate(int* leftIdx, int* rightIdx);
private:
	
private:
	std::vector<int>	m_MapData;
	CC_SYNTHESIZE_READONLY(int, m_Width, Width);
	CC_SYNTHESIZE_READONLY(int, m_Height, Height);
};