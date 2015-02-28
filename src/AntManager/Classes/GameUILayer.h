#pragma once

//GameScene�� �ִ� ���Ʒ� UI�� ��� ���̾�
class ScoreBoard;
class GameUILayer : public cocos2d::Layer
{
public:
	GameUILayer();
	virtual ~GameUILayer();
	virtual bool	init();
	void			sellMenuCallBack(cocos2d::Ref* ref);
	void			buyMenuCallBack(cocos2d::Ref* ref);
	CREATE_FUNC(GameUILayer);

private:
	void			makeButtons();

private:
	cocos2d::LabelTTF*	m_Score;
	cocos2d::LabelTTF*	m_AntsCount;
	ScoreBoard*			m_ScoreBoard;
};