#pragma once

class MapModel;
class MachineModel : public cocos2d::Object
{
public:
	MachineModel();
	virtual ~MachineModel();
	void		initMachine(int machineType);
	void		initFromFile(const std::string& filePath);
	bool		sellAnts(int numOfAnts);
	bool		buyAnts(int numOfAnts);
	MapModel*	getMapModel();

private:
	CC_SYNTHESIZE(int, m_AvailableAntsCount, AvailableAntsCount);
private:
	std::string	m_MapFilePath;
	int			m_ExchangeRate;
	MapModel*	m_MapModel;
};