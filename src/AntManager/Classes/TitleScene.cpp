#include "pch.h"
#include "TitleScene.h"
#include "GameManager.h"
#include "Type.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

bool TitleScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	makeButtons();
    return true;
}

void TitleScene::makeButtons()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto startItem = MenuItemFont::create("GAME START", CC_CALLBACK_1(TitleScene::menuStartCallback, this));
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(TitleScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + visibleSize.height - closeItem->getContentSize().height / 2));
	startItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));

	auto menu = Menu::create(closeItem, startItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void TitleScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void TitleScene::menuStartCallback(cocos2d::Ref* pSender)
{
	GET_GAME_MANAGER()->startGame(1);
}


