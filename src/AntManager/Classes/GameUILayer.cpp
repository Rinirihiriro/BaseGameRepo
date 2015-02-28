#include "Pch.h"
#include "GameUILayer.h"

USING_NS_CC;

GameUILayer::GameUILayer()
{
}

GameUILayer::~GameUILayer()
{
}

bool GameUILayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	makeButtons();
	return true;
}

void GameUILayer::makeButtons()
{
	auto sellButton = MenuItemSprite::create(
		Sprite::create("sell_button.png"), Sprite::create("sell_button.png"),
		CC_CALLBACK_1(GameUILayer::sellMenuCallBack, this));
	auto buyButton = MenuItemSprite::create(
		Sprite::create("buy_button.png"), Sprite::create("buy_button.png"), 
		CC_CALLBACK_1(GameUILayer::buyMenuCallBack, this));
	auto winSize = Director::getInstance()->getWinSize();
	Point sellButtonPos(0, 0);
	Point buyButtonPos(winSize.width, 0);
	sellButton->setPosition(sellButtonPos);
	sellButton->setAnchorPoint(Vec2::ZERO);
	buyButton->setPosition(buyButtonPos);
	buyButton->setAnchorPoint(Vec2(1, 0));
	addChild(sellButton);
	addChild(buyButton);
}

void GameUILayer::sellMenuCallBack(cocos2d::Ref* ref)
{

}

void GameUILayer::buyMenuCallBack(cocos2d::Ref* ref)
{

}
