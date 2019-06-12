#include "GameMenu.h"
#include "HitBrick.h"
#include "cocos2d.h"
#include "set1.h"
#include "Help.h"



Scene* GameMenu::createScene()

{
	auto scene = Scene::create();
	auto layer = GameMenu::create();
	scene->addChild(layer);
	return scene;
}



bool GameMenu::init()

{

	if (!Layer::init())
	{
		return false;
	}



	Size VisibleSize = Director::getInstance()->getVisibleSize();	//获得屏幕大小

	//开始游戏按钮
	auto  start_btn = Sprite::create("btn.png");
	start_btn->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.7));
	this->addChild(start_btn);
	auto label1 = Label::createWithSystemFont("开始游戏", "fonts/STXINWEI.TTF", 30);
	label1->setColor(Color3B(2, 0, 0));
	auto startbtn = MenuItemLabel::create(label1, CC_CALLBACK_1(GameMenu::EnterHitBrick, this));
	auto start = Menu::create(startbtn, NULL);
	start->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.7));
	this->addChild(start);


	//游戏设置
	auto  set_btn = Sprite::create("btn.png");
	set_btn->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.5));
	this->addChild(set_btn);
	auto label2 = Label::createWithSystemFont("游戏设置", "fonts/STXINWEI.TTF", 30);
	label2->setColor(Color3B(2, 0, 0));
	auto setbtn = MenuItemLabel::create(label2, CC_CALLBACK_1(GameMenu::EnterSet, this));
	auto set = Menu::create(setbtn, NULL);
	set->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.5));
	this->addChild(set);

	//游戏帮助界面
	auto  help_btn = Sprite::create("btn.png");
	help_btn->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.3));
	this->addChild(help_btn);
	auto label3 = Label::createWithSystemFont("帮助", "fonts/STXINWEI.TTF", 30);
	label3->setColor(Color3B(2, 0, 0));
	auto helpbtn = MenuItemLabel::create(label3, CC_CALLBACK_1(GameMenu::EnterHelp, this));
	auto help = Menu::create(helpbtn, NULL);
	help->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.3));
	this->addChild(help);
	/*auto label = Label::createWithSystemFont("Play", "fonts/arial.ttf", 30);

	auto menuitem = MenuItemLabel::create(label, CC_CALLBACK_1(GameMenu::EnterHitBrick, this));

	auto menu = Menu::create(menuitem, NULL);

	this->addChild(menu);

	return true;*/
}


//转移到游戏场景
void GameMenu::EnterHitBrick(Ref *pSender)
{
	Director::getInstance()->pushScene(HitBrick::createScene());
}

//转移到游戏设置场景
void GameMenu::EnterSet(Ref *pSender)
{
	Director::getInstance()->pushScene(set1::createScene());
}

//转移到游戏帮助场景
void GameMenu::EnterHelp(Ref *pSender)
{
	Director::getInstance()->pushScene(Help::createScene());
}