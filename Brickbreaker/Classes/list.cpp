#include "list.h"

#include "GameMenu.h"


#define database UserDefault::getInstance()


USING_NS_CC;
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

	//´¢´æÊý¾Ý
	if (database->getBoolForKey("bool", false)) {
		First = database->getIntegerForKey("FIRST_PLACE");
		Second = database->getIntegerForKey("SECOND_PLACE");
		Third = database->getIntegerForKey("THIRD_PLACE");
		Fourth = database->getIntegerForKey("FOURTH_PLACE");
		Fifth = database->getIntegerForKey("FIFTH_PLACE");
	}
	else {
		database->setBoolForKey("bool", true);
		database->setIntegerForKey("FIRST_PLACE", 0);
		database->setIntegerForKey("SECOND_PLACE", 0);
		database->setIntegerForKey("THIRD_PLACE", 0);
		database->setIntegerForKey("FOURTH_PLACE", 0);
		database->setIntegerForKey("FIFTH_PLACE", 0);
		database->flush();
	}

	auto list = Label::create("Ranking List", "fonts/STXINWEI.TTF", 40);
	list->setColor(Color3B(2, 0, 0));
	list->setPosition(Vec2(VisibleSize.width*0.5, VisibleSize.height*0.85));
	this->addChild(list);

	auto fir = Label::createWithSystemFont("First: 00", "fonts/STXINWEI.TTF", 32);
	fir->setString(StringUtils::format("First: %i", First));
	fir->setPosition(Vec2(VisibleSize.width*0.5, VisibleSize.height*0.75));
	this->addChild(fir,10);

	auto sec = Label::createWithSystemFont("Second: 00", "fonts/STXINWEI.TTF", 32);
	sec->setString(StringUtils::format("Second: %i", Second));
	sec->setPosition(Vec2(VisibleSize.width*0.5, VisibleSize.height*0.65));
	this->addChild(sec,10);

	auto thi = Label::createWithSystemFont("Third: 00", "fonts/STXINWEI.TTF", 32);
	thi->setString(StringUtils::format("Third: %i", Third));
	thi->setPosition(Vec2(VisibleSize.width*0.5, VisibleSize.height*0.55));
	this->addChild(thi,10);

	auto fou = Label::createWithSystemFont("Fourth: 00", "fonts/STXINWEI.TTF", 32);
	fou->setString(StringUtils::format("Fourth: %i", Fourth));
	fou->setPosition(Vec2(VisibleSize.width*0.5, VisibleSize.height*0.45));
	this->addChild(fou,10);

	auto fif = Label::createWithSystemFont("Fifth: 00", "fonts/STXINWEI.TTF", 32);
	fif->setString(StringUtils::format("Fifth: %i", Fifth));
	fif->setPosition(Vec2(VisibleSize.width*0.5, VisibleSize.height*0.35));
	this->addChild(fif,10);


	auto label = Label::create("Return", "fonts/STXINWEI.TTF", 40);
	label->setColor(Color3B(2, 0, 0));
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