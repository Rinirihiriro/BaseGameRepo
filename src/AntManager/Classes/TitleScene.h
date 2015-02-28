#pragma once

//첫 화면에서 인게임까지 이어주는 
class TitleScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene*	createScene();
    virtual bool			init();
    void					menuCloseCallback(cocos2d::Ref* pSender);
	void					menuStartCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(TitleScene);
private:
	void					makeButtons();
private:

};

