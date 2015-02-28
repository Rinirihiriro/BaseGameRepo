#pragma once
#include "json.h"

#define GET_DATA_MANAGER DataManager::getInstance

class MapModel;
class DataManager : public cocos2d::Object
{
public:
	static DataManager*	getInstance();
	void				releaseInstance();
	std::string			readFromFile(const std::string& filePath);
	Json::Value			toJsonFromString(const std::string& string);

private:
	DataManager();
	virtual ~DataManager();

private:
	static DataManager*	m_Instance;
};

