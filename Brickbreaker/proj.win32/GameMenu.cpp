#include "GameMenu.h"

#include "cocos2d.h"
#include "Help.h"
#include "mode_choose.h"
#include "list.h"


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

	auto background = Sprite::create("bg.png");
	background->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.5));
	background->setScale(VisibleSize.width / background->getContentSize().width, VisibleSize.height / background->getContentSize().height);
	this->addChild(background);

	//动画
	auto hero1 = Sprite::create("10001.png");
	hero1->setPosition(Vec2(VisibleSize.width*0.20, VisibleSize.height*0.5));
	hero1->setScale(0.3, 0.3);
	this->addChild(hero1);
	auto animation1 = Animation::create();

	for (int i = 1; i < 6; i++) {
		animation1->addSpriteFrameWithFile(StringUtils::format("1000%d.png", i));
	}
	animation1->setDelayPerUnit(3.0 / 5.0);
	animation1->setRestoreOriginalFrame(true);
	auto animate1 = Animate::create(animation1);
	auto repeat1 = RepeatForever::create(animate1);
	hero1->runAction(repeat1);

	auto hero2 = Sprite::create("10001.png");
	hero2->setPosition(Vec2(VisibleSize.width*0.8, VisibleSize.height*0.5));
	hero2->setScale(0.3, 0.3);
	this->addChild(hero2);
	auto animation2 = Animation::create();

	for (int i = 1; i < 6; i++) {
		animation2->addSpriteFrameWithFile(StringUtils::format("1000%d.png", i));
	}
	animation2->setDelayPerUnit(3.0 / 5.0);
	animation2->setRestoreOriginalFrame(true);
	auto animate2 = Animate::create(animation2);
	auto repeat2 = RepeatForever::create(animate2);
	hero2->runAction(repeat2);

	//开始游戏按钮
	auto  start_btn = Sprite::create("btn.png");
	start_btn->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.7));
	this->addChild(start_btn);
	auto label1 = Label::createWithSystemFont("Play Game", "fonts/STXINWEI.TTF", 30);
	label1->setColor(Color3B(2, 0, 0));
	auto startbtn = MenuItemLabel::create(label1, CC_CALLBACK_1(GameMenu::EnterHitBrick, this));
	auto start = Menu::create(startbtn, NULL);
	start->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.7));
	this->addChild(start);


	//游戏设置
	auto  set_btn = Sprite::create("btn.png");
	set_btn->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.5));
	this->addChild(set_btn);
	auto label2 = Label::createWithSystemFont("Ranking List", "fonts/STXINWEI.TTF", 30);
	label2->setColor(Color3B(2, 0, 0));
	auto setbtn = MenuItemLabel::create(label2, CC_CALLBACK_1(GameMenu::EnterSet, this));
	auto set = Menu::create(setbtn, NULL);
	set->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.5));
	this->addChild(set);

	//游戏帮助界面
	auto  help_btn = Sprite::create("btn.png");
	help_btn->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.3));
	this->addChild(help_btn);
	auto label3 = Label::createWithSystemFont("Help", "fonts/STXINWEI.TTF", 30);
	label3->setColor(Color3B(2, 0, 0));
	auto helpbtn = MenuItemLabel::create(label3, CC_CALLBACK_1(GameMenu::EnterHelp, this));
	auto help = Menu::create(helpbtn, NULL);
	help->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.3));
	this->addChild(help);

	return true;
}


//转移到游戏场景
void GameMenu::EnterHitBrick(Ref *pSender)
{
	Director::getInstance()->pushScene(mode_choose::createScene());
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