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



	Size VisibleSize = Director::getInstance()->getVisibleSize();	//�����Ļ��С

	auto background = Sprite::create("bg.png");
	background->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.5));
	background->setScale(VisibleSize.width / background->getContentSize().width, VisibleSize.height / background->getContentSize().height);
	this->addChild(background);

	//��ʼ��Ϸ��ť
	auto  start_btn = Sprite::create("btn.png");
	start_btn->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.7));
	this->addChild(start_btn);
	auto label1 = Label::createWithSystemFont("Play Game", "fonts/STXINWEI.TTF", 30);
	label1->setColor(Color3B(2, 0, 0));
	auto startbtn = MenuItemLabel::create(label1, CC_CALLBACK_1(GameMenu::EnterHitBrick, this));
	auto start = Menu::create(startbtn, NULL);
	start->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.7));
	this->addChild(start);


	//��Ϸ����
	auto  set_btn = Sprite::create("btn.png");
	set_btn->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.5));
	this->addChild(set_btn);
	auto label2 = Label::createWithSystemFont("Ranking List", "fonts/STXINWEI.TTF", 30);
	label2->setColor(Color3B(2, 0, 0));
	auto setbtn = MenuItemLabel::create(label2, CC_CALLBACK_1(GameMenu::EnterSet, this));
	auto set = Menu::create(setbtn, NULL);
	set->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.5));
	this->addChild(set);

	//��Ϸ��������
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


//ת�Ƶ���Ϸ����
void GameMenu::EnterHitBrick(Ref *pSender)
{
	Director::getInstance()->pushScene(mode_choose::createScene());
}

//ת�Ƶ���Ϸ���ó���
void GameMenu::EnterSet(Ref *pSender)
{
	Director::getInstance()->pushScene(set1::createScene());
}

//ת�Ƶ���Ϸ��������
void GameMenu::EnterHelp(Ref *pSender)
{
	Director::getInstance()->pushScene(Help::createScene());
}