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
	if (database->getBoolForKey("bool1", false)&& database->getBoolForKey("bool2", false)&& database->getBoolForKey("bool3", false)) {
		First[0] = database->getIntegerForKey("FIRST_PLACE1");
		Second[0] = database->getIntegerForKey("SECOND_PLACE1");
		Third[0] = database->getIntegerForKey("THIRD_PLACE1");
		Fourth[0] = database->getIntegerForKey("FOURTH_PLACE1");
		Fifth[0] = database->getIntegerForKey("FIFTH_PLACE1");
		First[1] = database->getIntegerForKey("FIRST_PLACE2");
		Second[1] = database->getIntegerForKey("SECOND_PLACE2");
		Third[1] = database->getIntegerForKey("THIRD_PLACE2");
		Fourth[1] = database->getIntegerForKey("FOURTH_PLACE2");
		Fifth[1] = database->getIntegerForKey("FIFTH_PLACE2");
		First[2] = database->getIntegerForKey("FIRST_PLACE3");
		Second[2] = database->getIntegerForKey("SECOND_PLACE3");
		Third[2] = database->getIntegerForKey("THIRD_PLACE3");
		Fourth[2] = database->getIntegerForKey("FOURTH_PLACE3");
		Fifth[2] = database->getIntegerForKey("FIFTH_PLACE3");
	}
	else {
		database->setBoolForKey("bool1", true); database->setBoolForKey("bool2", true); database->setBoolForKey("bool3", true);
		database->setIntegerForKey("FIRST_PLACE1", 0);
		database->setIntegerForKey("SECOND_PLACE1", 0);
		database->setIntegerForKey("THIRD_PLACE1", 0);
		database->setIntegerForKey("FOURTH_PLACE1", 0);
		database->setIntegerForKey("FIFTH_PLACE1", 0);
		database->setIntegerForKey("FIRST_PLACE2", 0);
		database->setIntegerForKey("SECOND_PLACE2", 0);
		database->setIntegerForKey("THIRD_PLACE2", 0);
		database->setIntegerForKey("FOURTH_PLACE2", 0);
		database->setIntegerForKey("FIFTH_PLACE2", 0);
		database->setIntegerForKey("FIRST_PLACE3", 0);
		database->setIntegerForKey("SECOND_PLACE3", 0);
		database->setIntegerForKey("THIRD_PLACE3", 0);
		database->setIntegerForKey("FOURTH_PLACE3", 0);
		database->setIntegerForKey("FIFTH_PLACE3", 0);
		database->flush();
	}

	auto list = Label::create("Ranking List", "fonts/STXINWEI.TTF", 40);
	list->setColor(Color3B(2, 0, 0));
	list->setPosition(Vec2(VisibleSize.width*0.5, VisibleSize.height*0.85));
	this->addChild(list);

	auto fir = Label::createWithSystemFont("First: 00", "fonts/STXINWEI.TTF", 32);
	fir->setString(StringUtils::format("First: %i %i %i", First[0], First[1], First[2]));
	fir->setPosition(Vec2(VisibleSize.width*0.5, VisibleSize.height*0.75));
	this->addChild(fir,10);

	auto sec = Label::createWithSystemFont("Second: 00", "fonts/STXINWEI.TTF", 32);
	sec->setString(StringUtils::format("Second: %i %i %i", Second[0], Second[1], Second[2]));
	sec->setPosition(Vec2(VisibleSize.width*0.5, VisibleSize.height*0.65));
	this->addChild(sec,10);

	auto thi = Label::createWithSystemFont("Third: 00", "fonts/STXINWEI.TTF", 32);
	thi->setString(StringUtils::format("Third: %i %i %i", Third[0], Third[1], Third[2]));
	thi->setPosition(Vec2(VisibleSize.width*0.5, VisibleSize.height*0.55));
	this->addChild(thi,10);

	auto fou = Label::createWithSystemFont("Fourth: 00", "fonts/STXINWEI.TTF", 32);
	fou->setString(StringUtils::format("Fourth: %i %i %i", Fourth[0], Fourth[1], Fourth[2]));
	fou->setPosition(Vec2(VisibleSize.width*0.5, VisibleSize.height*0.45));
	this->addChild(fou,10);

	auto fif = Label::createWithSystemFont("Fifth: 00", "fonts/STXINWEI.TTF", 32);
	fif->setString(StringUtils::format("Fifth: %i %i %i", Fifth[0], Fifth[1], Fifth[2]));
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