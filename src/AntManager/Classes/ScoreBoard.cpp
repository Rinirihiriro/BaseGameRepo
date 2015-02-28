#include "Pch.h"
#include "ScoreBoard.h"
#include "GameManager.h"
#include "PlayerModel.h"
#include "MachineModel.h"

USING_NS_CC;

ScoreBoard::ScoreBoard()
{

}

ScoreBoard::~ScoreBoard()
{

}

bool ScoreBoard::init()
{
	if(!Node::init())
	{
		return false;
	}
	makeLabels();
	makeSprites();
	updateBoard();
	return true;
}

void ScoreBoard::updateBoard()
{
	int curMoney = GET_GAME_MANAGER()->getPlayer()->getMoney();
	int curAnts = GET_GAME_MANAGER()->getMachine()->getAvailableAntsCount();
	m_Money->setString(std::to_string(curMoney));
	m_Ants->setString(std::to_string(curAnts));
}

void ScoreBoard::makeLabels()
{
	m_Money = Label::createWithSystemFont("100", "consolas", 30);
	m_Ants = Label::createWithSystemFont("100", "consolas", 30);
	m_Money->setColor(Color3B::BLACK);
	m_Ants->setColor(Color3B::BLACK);
	
	auto winSize = Director::getInstance()->getWinSize();
	Point moneyPos(50, winSize.height);
	Point antPos(250, winSize.height);
	
	m_Money->setPosition(moneyPos);
	m_Ants->setPosition(antPos);
	m_Money->setAnchorPoint(Vec2(0, 1));
	m_Ants->setAnchorPoint(Vec2(0, 1));
	addChild(m_Money);
	addChild(m_Ants);
}

void ScoreBoard::makeSprites()
{
	auto antSprite = Sprite::create("ant_black.png");
	auto coinSprite = Sprite::create("coin.png");
	auto winSize = Director::getInstance()->getWinSize();
	Point moneyPos(0, winSize.height - 0);
	Point antPos(200, winSize.height - 0);

	coinSprite->setScale(2.f);
	antSprite->setScale(2.f);
	coinSprite->setPosition(moneyPos);
	antSprite->setPosition(antPos);
	coinSprite->setAnchorPoint(Vec2(0, 1));
	antSprite->setAnchorPoint(Vec2(0, 1));
	addChild(coinSprite);
	addChild(antSprite);
}
