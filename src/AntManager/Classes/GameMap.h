#pragma once

class MapModel;
class MapTile;
class GameMap : public cocos2d::Node
{
public:
	GameMap();
	virtual ~GameMap();
	virtual bool	init();
	void			initWithModel(MapModel* mapModel);
	void			makeTiles();
	CREATE_FUNC(GameMap);

private:
	std::vector<MapTile*>	m_Tiles;
	MapModel*				m_MapModel;
};