#pragma once

class MapModel;
class MapTile;
class Ant;
class Area;
class GameMap : public cocos2d::Node
{
public:
	GameMap();
	virtual ~GameMap();
	virtual bool	init();
	void			initWithModel(MapModel* mapModel);
	void			addAnt();

	CREATE_FUNC(GameMap);

private:
	void			makeTiles();
	void			makeAreas();
	void			addListener();

private:
	std::vector<Area*>		m_Areas;
	std::vector<MapTile*>	m_Tiles;
	std::vector<Ant*>		m_Ants;
	MapModel*				m_MapModel;
};