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
private:
	cocos2d::LabelTTF*	m_Label;
	cocos2d::LabelTTF*	m_Score;
};