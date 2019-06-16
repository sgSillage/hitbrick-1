#include "mode_choose.h"
#include"HitBrick.h"
#include"HitBrick_Double.h"


mode_choose::mode_choose(){}


mode_choose::~mode_choose(){}


Scene* mode_choose::createScene() {
	auto scene = Scene::create();
	auto layer = mode_choose::create();
	scene->addChild(layer);
	return scene;
}

bool mode_choose::init() {

	if (!Layer::init()) {
		return false;
	}

	Size VisibleSize = Director::getInstance()->getVisibleSize();	//获得屏幕大小

	auto background = Sprite::create("bg.png");
	background->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.5));
	background->setScale(VisibleSize.width / background->getContentSize().width, VisibleSize.height / background->getContentSize().height);
	this->addChild(background);

	auto  solo_btn = Sprite::create("btn.png");
	solo_btn->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.6));
	this->addChild(solo_btn);
	auto label1 = Label::createWithSystemFont("Solo", "fonts/STXINWEI.TTF", 30);
	label1->setColor(Color3B(2, 0, 0));
	auto solobtn = MenuItemLabel::create(label1, CC_CALLBACK_1(mode_choose::solomode, this));
	auto solo = Menu::create(solobtn, NULL);
	solo->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.6));
	this->addChild(solo);

	auto  pk_btn = Sprite::create("btn.png");
	pk_btn->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.4));
	this->addChild(pk_btn);
	auto label2 = Label::createWithSystemFont("PK!!", "fonts/STXINWEI.TTF", 30);
	label2->setColor(Color3B(2, 0, 0));
	auto pkbtn = MenuItemLabel::create(label2, CC_CALLBACK_1(mode_choose::pkmode, this));
	auto pk = Menu::create(pkbtn, NULL);
	pk->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height*0.4));
	this->addChild(pk);


}


void mode_choose::solomode(Ref* pSender) {
	Director::getInstance()->pushScene(HitBrick::createScene());
}

void mode_choose::pkmode(Ref* pSender) {
	Director::getInstance()->pushScene(HitBrick_Double::createScene());
}