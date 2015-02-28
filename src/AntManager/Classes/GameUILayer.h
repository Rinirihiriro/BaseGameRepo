#pragma once

//GameScene에 있는 위아래 UI를 담는 레이어

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
};