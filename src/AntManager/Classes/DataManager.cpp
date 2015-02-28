#include "Pch.h"
#include "DataManager.h"
#include "MapModel.h"
#include "Macro.h"
#include "Define.h"

DataManager* DataManager::m_Instance = nullptr;

DataManager::DataManager()
	:m_MapModel(nullptr)
{
}

DataManager::~DataManager()
{
}

DataManager* DataManager::getInstance()
{
	if(m_Instance == nullptr)
	{
		m_Instance = new DataManager();
	}
	return m_Instance;
}

void DataManager::releaseInstance()
{
	SAFE_DELETE(m_Instance);
}


std::string DataManager::readFromFile(const std::string& filePath)
{
	std::string data;
	FILE* file = fopen(filePath.c_str(), "rb");
	char ch;
	if(file != NULL)
	{
		while(EOF != (ch = fgetc(file)))
		{
			data += ch;
		}
	}

	fclose(file);
	return data;
}

Json::Value DataManager::toJsonFromString(const std::string& string)
{
	Json::Value root;
	Json::Reader reader;
	bool isSuccess = reader.parse(string, root);
	return root;
}

MapModel* DataManager::getMapModel()
{
	//문제있는 코드
	if(m_MapModel == nullptr)
	{
		m_MapModel = new MapModel();
		m_MapModel->initFromFile(MAP_DATA_01);
	}
	return m_MapModel;
}

