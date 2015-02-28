#include "Pch.h"
#include "ScoreBoard.h"

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
	return true;
}

void ScoreBoard::updateBoard()
{

}

void ScoreBoard::makeLabels()
{
	m_Money = Label::createWithSystemFont("100", "consolas", 30);
	m_Ants = Label::createWithSystemFont("100", "consolas", 30);
	m_Money->setColor(Color3B::BLACK);
	m_Ants->setColor(Color3B::BLACK);
	
	auto winSize = Director::getInstance()->getWinSize();
	Point moneyPos(0, winSize.height);
	Point antPos(200, winSize.height);
	
	m_Money->setPosition(moneyPos);
	m_Ants->setPosition(antPos);
	m_Money->setAnchorPoint(Vec2(0, 1));
	m_Ants->setAnchorPoint(Vec2(0, 1));
	addChild(m_Money);
	addChild(m_Ants);
}

void ScoreBoard::makeSprites()
{

}
