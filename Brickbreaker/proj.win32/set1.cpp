#include "set1.h"

#include "GameMenu.h"

set1::set1(){}


set1::~set1(){}


Scene *set1::createScene()
{
	auto scene = Scene::create();
	auto layer = set1::create();
	scene->addChild(layer);
	return scene;
}

bool set1::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size VisibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("bg.png");
	background->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.5));
	background->setScale(VisibleSize.width / background->getContentSize().width, VisibleSize.height / background->getContentSize().height);
	this->addChild(background);

	
	auto label = Label::create("Return", "fonts/STXINWEI.TTF", 40);
	auto exitbtn = MenuItemLabel::create(label, CC_CALLBACK_1(set1::exitSet1,this));
	auto exit = Menu::create(exitbtn, NULL);
	exit->setPosition(Vec2(VisibleSize.width*0.9, VisibleSize.height*0.1));
	this->addChild(exit);
	
	return true;
}

void set1::exitSet1(Ref *pSender)
{
	Director::getInstance()->replaceScene(GameMenu::createScene());
}