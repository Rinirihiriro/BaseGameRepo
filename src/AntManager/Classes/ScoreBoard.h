#pragma once

class ScoreBoard : public cocos2d::Node
{
public:
	ScoreBoard();
	virtual ~ScoreBoard();
	virtual bool	init();
	void			updateBoard();
	CREATE_FUNC(ScoreBoard);

private:
	void			makeLabels();
	void			makeSprites();
	void			addListener();

private:
	cocos2d::Label*	m_Ants;
	cocos2d::Label*	m_Money;
};