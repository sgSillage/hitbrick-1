#include "Help.h"

#include "GameMenu.h"

Help::Help()
{
}


Help::~Help()
{
}

Scene *Help::createScene()
{
	auto scene = Scene::create();
	auto layer = Help::create();
	scene->addChild(layer);
	return scene;
}

bool Help::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size VisibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("bg.png");
	background->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.5));
	background->setScale(VisibleSize.width / background->getContentSize().width, VisibleSize.height / background->getContentSize().height);
	this->addChild(background);

	//文本框




	//退出按钮
	auto label = Label::create("Return", "fonts/STXINWEI.TTF", 40);
	label->setColor(Color3B(2, 0, 0));
	auto exitbtn = MenuItemLabel::create(label, CC_CALLBACK_1(Help::exitHelp, this));
	auto exit = Menu::create(exitbtn, NULL);
	exit->setPosition(Vec2(VisibleSize.width*0.9, VisibleSize.height*0.1));
	this->addChild(exit);

	return true;
}

void Help::exitHelp(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameMenu::createScene());
}