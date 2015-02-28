#include "Pch.h"
#include "GameUILayer.h"
#include "GameManager.h"
#include "MachineModel.h"
#include "ScoreBoard.h"
#include "Macro.h"

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
	makeScoreBoard();
	return true;
}

void GameUILayer::makeButtons()
{
	auto sellButton = MenuItemSprite::create(
		Sprite::create("sell_button.png"), Sprite::create("sell_button_pressed.png"),
		CC_CALLBACK_1(GameUILayer::sellMenuCallBack, this));
	auto buyButton = MenuItemSprite::create(
		Sprite::create("buy_button.png"), Sprite::create("buy_button_pressed.png"), 
		CC_CALLBACK_1(GameUILayer::buyMenuCallBack, this));
	auto winSize = Director::getInstance()->getWinSize();

	Point sellButtonPos(0, 0);
	Point buyButtonPos(winSize.width, 0);

	sellButton->setPosition(sellButtonPos);
	sellButton->setAnchorPoint(Vec2::ZERO);
	buyButton->setPosition(buyButtonPos);
	buyButton->setAnchorPoint(Vec2(1, 0));

	auto menu = Menu::create(sellButton, buyButton, NULL);
	menu->setAnchorPoint(Vec2::ZERO);
	menu->setPosition(Point(0, 0));
	addChild(menu);
}

void GameUILayer::sellMenuCallBack(cocos2d::Ref* ref)
{
	if(GET_GAME_MANAGER()->getMachine()->sellAnts(1))
	{

	}
}

void GameUILayer::buyMenuCallBack(cocos2d::Ref* ref)
{
	if(GET_GAME_MANAGER()->getMachine()->buyAnts(1))
	{
		EVENT_DISPATCH("add Ant");
	}
}

void GameUILayer::makeScoreBoard()
{
	m_ScoreBoard = ScoreBoard::create();
	addChild(m_ScoreBoard);
}
