#pragma execution_character_set("utf-8")



#include "level2.h"

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

#include "GameMenu.h"

#include "mode_choose.h"

#include "HitBrick.h"

#include "level3.h"



#define database UserDefault::getInstance()

USING_NS_CC;

using namespace CocosDenshion;

void level2::setPhysicsWorld(PhysicsWorld* world) { m_world = world; }

Scene* level2::createScene() {
	srand((unsigned)time(NULL));

	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setAutoStep(true);

	// Debug 模式


	// scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setGravity(Vec2(0, -300.0f));

	auto layer = level2::create();

	layer->setPhysicsWorld(scene->getPhysicsWorld());
	layer->setJoint();
	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance

bool level2::init() {

	//////////////////////////////

	// 1. super init first

	if (!Layer::init()) {
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	auto edgeSp = Sprite::create();  //创建一个精灵

	auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 1.0f, 0.0f), 3);  //edgebox是不受刚体碰撞影响的一种刚体，我们用它来设置物理世界的边界

	edgeSp->setPosition(visibleSize.width / 2, visibleSize.height / 2);  //位置设置在屏幕中央

	edgeSp->setPhysicsBody(boundBody);

	addChild(edgeSp);

	//储存数据
	if (database->getBoolForKey("bool2", false)) {
		First = database->getIntegerForKey("FIRST_PLACE2");
		Second = database->getIntegerForKey("SECOND_PLACE2");
		Third = database->getIntegerForKey("THIRD_PLACE2");
		Fourth = database->getIntegerForKey("FOURTH_PLACE2");
		Fifth = database->getIntegerForKey("FIFTH_PLACE2");
	}
	else {
		database->setBoolForKey("bool2", true);
		database->setIntegerForKey("FIRST_PLACE2", 0);
		database->setIntegerForKey("SECOND_PLACE2", 0);
		database->setIntegerForKey("THIRD_PLACE2", 0);
		database->setIntegerForKey("FOURTH_PLACE2", 0);
		database->setIntegerForKey("FIFTH_PLACE2", 0);
		database->flush();
	}
	//小球
	auto box = Sprite::create("box.png");
	int xbox = box->getContentSize().width; int ybox = box->getContentSize().height;

	//分数
	auto score_btn = Sprite::create("btn.png");
	score_btn->setScale(0.7, 0.5);
	score_btn->setAnchorPoint(Vec2(0, 0.7));
	score_btn->setPosition(Vec2(15, visibleSize.height));
	this->addChild(score_btn, 10);
	_scoreLabel = Label::createWithSystemFont("积分：00", "fonts/arial.ttf", 32);
	_scoreLabel->setPosition(100, visibleSize.height * 0.955);
	this->addChild(_scoreLabel, 10);



	//关卡号码
	auto level_btn = Sprite::create("btn.png");
	level_btn->setScale(0.7, 0.5);
	level_btn->setAnchorPoint(Vec2(0, 0.7));
	level_btn->setPosition(Vec2(45 + score_btn->getContentSize().width, visibleSize.height));
	this->addChild(level_btn, 10);
	auto levelLabel = Label::create("Level: 2", "fonts/arial.ttf", 32);
	levelLabel->setPosition(score_btn->getContentSize().width + 115, visibleSize.height * 0.955);
	this->addChild(levelLabel, 11);

	//目标分数
	target_score = 100;
	auto target_btn = Sprite::create("btn.png");
	target_btn->setScale(0.7, 0.5);
	target_btn->setAnchorPoint(Vec2(0, 0.7));
	target_btn->setPosition(Vec2(30 + 2 * score_btn->getContentSize().width, visibleSize.height));
	this->addChild(target_btn, 10);
	auto targetLabel = Label::create("Target: 00", "fonts/arial.ttf", 32);
	targetLabel->setString(StringUtils::format("Target: %i", target_score));
	targetLabel->setPosition(2 * score_btn->getContentSize().width + 130, visibleSize.height * 0.955);
	this->addChild(targetLabel, 11);

	//返回按钮
	auto labelF = Label::create("Return", "fonts/STXINWEI.TTF", 30);
	labelF->setColor(Color3B(2, 0, 0));
	auto exitbtnF = MenuItemLabel::create(labelF, CC_CALLBACK_1(level2::returnMenu, this));
	auto exitF = Menu::create(exitbtnF, NULL);
	exitF->setPosition(Vec2(visibleSize.width*0.9, visibleSize.height*0.955));
	this->addChild(exitF, 12);




	preloadMusic(); // 预加载音效

	addSprite();    // 添加背景和各种精灵

	addListener();  // 添加监听器 

	addPlayer();    // 添加球与板

	BrickGeneraetd();  // 生成砖块



	schedule(schedule_selector(level2::update), 0.01f, kRepeatForever, 0.1f);
	//schedule(schedule_selector(level2::updateReadylong), 1.0f, kRepeatForever, 0.01f);


	onBall = true;

	spHolded = -1;

	spFactor = 0;

	readylong = 0;

	onBig = false;

	bigtime = 0;




	return true;
}

// 关节连接，固定球与板子

// Todo

void level2::setJoint() {

	Vec2 fixPoint = Vec2(ball->getAnchorPoint().x, ball->getAnchorPoint().y - 30);

	joint1 = PhysicsJointPin::construct(ball->getPhysicsBody(), player->getPhysicsBody(), fixPoint, player->getAnchorPoint());

	m_world->addJoint(joint1);
}

// 预加载音效

void level2::preloadMusic() {

	auto sae = SimpleAudioEngine::getInstance();

	sae->preloadEffect("gameover.mp3");

	sae->preloadBackgroundMusic("bgm.mp3");

	sae->playBackgroundMusic("bgm.mp3", true);
}

// 添加背景和各种精灵

void level2::addSprite() {

	// add background

	auto bgSprite = Sprite::create("bg.png");

	bgSprite->setPosition(visibleSize / 2);

	bgSprite->setScale(visibleSize.width / bgSprite->getContentSize().width, visibleSize.height / bgSprite->getContentSize().height);

	this->addChild(bgSprite, 0);

	//add bar

	blackbar = Sprite::create("blackbar.png");

	blackbar->setScale(visibleSize.width / blackbar->getContentSize().width, 0.2);

	blackbar->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height - 50));

	auto blbarbody = PhysicsBody::createBox(blackbar->getContentSize(), PhysicsMaterial(1000.0f, 1.0f, 10.0f));

	blbarbody->setCategoryBitmask(0xFFFFFFFF);

	blbarbody->setCollisionBitmask(0xFFFFFFFF);

	blbarbody->setContactTestBitmask(0xFFFFFFFF);

	blbarbody->setGravityEnable(false);

	blbarbody->setTag(3);

	blbarbody->setDynamic(false);

	blackbar->setPhysicsBody(blbarbody);

	//player->getPhysicsBody()->setRotationEnable(false);

	this->addChild(blackbar, 2);
	// add ship

	ship = Sprite::create("ship.png");

	ship->setScale(visibleSize.width / ship->getContentSize().width * 0.97, 1.0f);

	ship->setPosition(visibleSize.width / 2, 0);

	auto shipbody = PhysicsBody::createBox(ship->getContentSize(), PhysicsMaterial(100.0f, 0.0f, 1.0f));

	shipbody->setCategoryBitmask(0xFFFFFFFF);

	shipbody->setCollisionBitmask(0xFFFFFFFF);

	shipbody->setContactTestBitmask(0xFFFFFFFF);

	shipbody->setTag(Tag::SHIP);

	shipbody->setDynamic(false);

	ship->setPhysicsBody(shipbody);

	this->addChild(ship, 1);



	// add sun and cloud

	auto sunSprite = Sprite::create("sun.png");

	sunSprite->setPosition(rand() % (int)(visibleSize.width - 200) + 100, 550);

	this->addChild(sunSprite);

	auto cloudSprite1 = Sprite::create("cloud.png");

	cloudSprite1->setPosition(rand() % (int)(visibleSize.width - 200) + 100, rand() % 100 + 450);

	this->addChild(cloudSprite1);

	auto cloudSprite2 = Sprite::create("cloud.png");



	cloudSprite2->setPosition(rand() % (int)(visibleSize.width - 200) + 100, rand() % 100 + 450);



	this->addChild(cloudSprite2);

}



// 添加监听器



void level2::addListener() {

	auto keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(level2::onKeyPressed, this);

	keyboardListener->onKeyReleased = CC_CALLBACK_2(level2::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);



	auto contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(level2::onConcactBegin, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}







// 创建角色



void level2::addPlayer() {

	player = Sprite::create("bar.png");
	int xpos = visibleSize.width / 2;

	player->setScale(0.15f, 0.1f);

	player->setPosition(Vec2(xpos, ship->getContentSize().height - player->getContentSize().height*0.1f));

	// 设置板的刚体属性
	// Todo
	auto playerBody = PhysicsBody::createBox(player->getContentSize(), PhysicsMaterial(1000.0f, 1.0f, 10.0f));

	playerBody->setCategoryBitmask(0xFFFFFFFF);

	playerBody->setCollisionBitmask(0xFFFFFFFF);

	playerBody->setContactTestBitmask(0xFFFFFFFF);

	playerBody->setGravityEnable(false);

	playerBody->setTag(Tag::BOARD);

	player->setPhysicsBody(playerBody);

	player->getPhysicsBody()->setRotationEnable(false);

	this->addChild(player, 2);

	ball = Sprite::create("ball.png");

	ball->setPosition(Vec2(xpos, player->getPosition().y + ball->getContentSize().height*0.1f));

	ball->setScale(0.1f, 0.1f);

	// 设置球的刚体属性
	// Todo
	auto ballBody = PhysicsBody::createCircle(ball->getContentSize().height / 2, PhysicsMaterial(0.1f, 1.0f, 0.0f));

	ballBody->setCategoryBitmask(0xFFFFFFFF);

	ballBody->setCollisionBitmask(0xFFFFFFFF);

	ballBody->setContactTestBitmask(0xFFFFFFFF);

	ballBody->setGravityEnable(false);

	ballBody->setTag(Tag::BALL);

	ballBody->setRotationEnable(false);

	ball->setPhysicsBody(ballBody);

	addChild(ball, 3);
}

// 实现简单的蓄力效果

// Todo

//不让板在边界100像素以内以及蓄力

void level2::update(float dt) {

	//不让板越过边界
	if (player->getPosition().x < 100) {
		player->setPosition(100, player->getPosition().y);
		player->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
	else if (player->getPosition().x > visibleSize.width - 100)
	{
		player->setPosition(visibleSize.width - 100, player->getPosition().y);
		player->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}

	//蓄力及蓄力条的部分
	if (spHolded == 1 && spFactor <= 30) {
		spFactor++;
	}
	if (spHolded == 1) {
		readylong = spFactor * 0.03;
		ReadyB->setScale(readylong, 0.9);
	}
	if (spFactor == 30) {
		ready->removeFromParentAndCleanup(true);
		go = Label::create("Go!", "STXINWEI", 60);
		this->addChild(go, 12);
	}


	//BLUEBOOK部分
	if (onBig && bigtime == 0) {
		//道具所用板
		bigplayer = Sprite::create("bar.png");
		bigplayer->setScale(visibleSize.width / bigplayer->getContentSize().width, 0.1f);
		bigplayer->setPosition(Vec2(visibleSize.width*0.5, ship->getContentSize().height - bigplayer->getContentSize().height*0.1f + 50));

		// 设置板的刚体属性
		// Todo
		auto playerBody = PhysicsBody::createBox(bigplayer->getContentSize(), PhysicsMaterial(1000.0f, 1.0f, 10.0f));

		playerBody->setCategoryBitmask(0xFFFFFFFF);

		playerBody->setCollisionBitmask(0xFFFFFFFF);

		playerBody->setContactTestBitmask(0xFFFFFFFF);

		playerBody->setGravityEnable(false);

		playerBody->setTag(Tag::BOARD);

		playerBody->setDynamic(false);

		bigplayer->setPhysicsBody(playerBody);

		bigplayer->getPhysicsBody()->setRotationEnable(false);

		this->addChild(bigplayer, 2);
		bigtime++;
	}
	else if (onBig) {
		bigtime++;
		if (bigtime >= 300) {
			bigtime += 0;
			bigplayer->removeFromParentAndCleanup(true);
			onBig = false;
		}
	}

	Vec2 velocity = ball->getPhysicsBody()->getVelocity();
	//ball->getPhysicsBody()->setVelocity(velocity*(1 + _scorevalue * 0.3));
}



void level2::updateReadylong(float dt)
{
	Vec2 velocity = ball->getPhysicsBody()->getVelocity();
	ball->getPhysicsBody()->setVelocity(velocity*(1 + _scorevalue * 0.1));
}

// Todo

//添加砖块   

void level2::BrickGeneraetd() {
	for (int i = 1; i < 4; i++) {
		int cw = 30;
		while (cw <= visibleSize.width) {

			if (cw == 178 && i == 2) {
				auto box = Sprite::create("redbook.png");

				box->setPosition(cw, visibleSize.height - box->getContentSize().height * (i + 1));

				cw += box->getContentSize().width;

				auto boxBody = PhysicsBody::createCircle(box->getContentSize().height / 2, PhysicsMaterial(100.0f, 1.0f, 0.0f));

				boxBody->setCategoryBitmask(0xFFFFFFFF);

				boxBody->setCollisionBitmask(0xFFFFFFFF);

				boxBody->setContactTestBitmask(0xFFFFFFFF);

				boxBody->setGravityEnable(false);

				boxBody->setTag(Tag::REDBOOK);

				boxBody->setDynamic(false);

				box->setPhysicsBody(boxBody);

				box->getPhysicsBody()->setRotationEnable(false);

				addChild(box, 4);
			}

			else if (cw == 1066 && i == 2) {

				auto box = Sprite::create("bluebook.png");

				box->setPosition(cw, visibleSize.height - box->getContentSize().height * (i + 1));

				cw += box->getContentSize().width;

				auto boxBody = PhysicsBody::createCircle(box->getContentSize().height / 2, PhysicsMaterial(100.0f, 1.0f, 0.0f));

				boxBody->setCategoryBitmask(0xFFFFFFFF);

				boxBody->setCollisionBitmask(0xFFFFFFFF);

				boxBody->setContactTestBitmask(0xFFFFFFFF);

				boxBody->setGravityEnable(false);

				boxBody->setTag(Tag::BLUEBOOK);

				boxBody->setDynamic(false);

				box->setPhysicsBody(boxBody);

				box->getPhysicsBody()->setRotationEnable(false);

				addChild(box, 4);
			}


			else {
				auto box = Sprite::create("box.png");
				// 为砖块设置刚体属性
				// Todo

				box->setPosition(cw, visibleSize.height - box->getContentSize().height * (i + 1));

				cw += box->getContentSize().width;

				auto boxBody = PhysicsBody::createCircle(box->getContentSize().height / 2, PhysicsMaterial(100.0f, 1.0f, 0.0f));

				boxBody->setCategoryBitmask(0xFFFFFFFF);

				boxBody->setCollisionBitmask(0xFFFFFFFF);

				boxBody->setContactTestBitmask(0xFFFFFFFF);

				boxBody->setGravityEnable(false);

				boxBody->setTag(Tag::BOX);

				boxBody->setDynamic(false);

				box->setPhysicsBody(boxBody);

				box->getPhysicsBody()->setRotationEnable(false);

				addChild(box, 4);
			}
		}
	}
}


// 左右

void level2::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {

	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (player->getPosition().x > 100) {
			player->getPhysicsBody()->setVelocity(Vec2(-575, 0));
		}
		else {
			//player->setPosition(100, player->getPosition().y);
			player->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		// 左右移动
		// Todo
		if (player->getPosition().x < visibleSize.width - 100) {
			player->getPhysicsBody()->setVelocity(Vec2(575, 0));
		}
		else {
			//player->setPosition(visibleSize.width-100,player->getPosition().y);
			player->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE: // 开始蓄力
		if (spHolded == -1) {
			spHolded = 1;
			ready = Label::create("Ready!", "STXINWEI", 60);
			ready->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5 + 150));
			this->addChild(ready, 12);

			//蓄力进度条
			ReadyW = Sprite::create("whitebar.png");
			ReadyB = Sprite::create("blackbar.png");
			ReadyB->setAnchorPoint(Vec2(0, 0.5));
			//schedule(schedule_selector(HitBrick::updateReadylong), 0.01f);
			ReadyW->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
			ReadyB->setPosition(Vec2(visibleSize.width*0.5 - ReadyB->getContentSize().width*0.5 + 10, visibleSize.height*0.5));
			this->addChild(ReadyW, 88);
			this->addChild(ReadyB, 90);
		}
		break;
	default:
		break;
	}
}

// 释放按键

void level2::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		// 停止运动
		// Todo
		player->getPhysicsBody()->setVelocity(Vec2(0, 0));
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:   // 蓄力结束，小球发射
		if (spHolded == 1) {
			spHolded = 0;
			//go->removeFromParentAndCleanup(true);
			ReadyW->removeFromParentAndCleanup(true);
			ReadyB->removeFromParentAndCleanup(true);
			m_world->removeJoint(joint1);
			ball->getPhysicsBody()->setVelocity(Vec2(0, spFactor * 24));
		}
		break;
	default:
		break;
	}
}

// 碰撞检测
// Todo
bool level2::onConcactBegin(PhysicsContact & contact) {
	auto c1 = contact.getShapeA()->getBody(), c2 = contact.getShapeB()->getBody();

	auto s1 = (Sprite*)c1->getNode(), s2 = (Sprite*)c2->getNode();

	auto rain = ParticleRain::create();
	auto galaxy = ParticleGalaxy::create();

	auto rotate1 = RotateBy::create(0.5, 60);
	auto rotate2 = RotateBy::create(0.5, 30);

	if (c1->getTag() == Tag::BOX && c2->getTag() == Tag::BALL) {
		//下雨
		rain->setPosition(s1->getPosition());
		addChild(rain);
		//星光
		galaxy->setPosition(s1->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);
		s1->removeFromParentAndCleanup(true);
		//分数
		_scoreLabel->setString(StringUtils::format("积分：%i", _scorevalue += 50));

		ball->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c2->getTag() == Tag::BOX && c1->getTag() == Tag::BALL) {
		rain->setPosition(s2->getPosition());
		addChild(rain);

		galaxy->setPosition(s2->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);

		_scoreLabel->setString(StringUtils::format("积分：%i", _scorevalue += 50));

		s2->removeFromParentAndCleanup(true);
		ball->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c1->getTag() == Tag::REDBOOK && c2->getTag() == Tag::BALL) {
		//下雨
		rain->setPosition(s1->getPosition());
		addChild(rain);
		//星光
		galaxy->setPosition(s1->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);
		s1->removeFromParentAndCleanup(true);
		//道具效果
		level2::Redfunc();
		ball->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c2->getTag() == Tag::REDBOOK && c1->getTag() == Tag::BALL) {
		rain->setPosition(s2->getPosition());
		addChild(rain);

		galaxy->setPosition(s2->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);

		//道具效果
		level2::Redfunc();

		s2->removeFromParentAndCleanup(true);
		ball->runAction(Sequence::create(rotate1, rotate2, NULL));
	}


	else if (c1->getTag() == Tag::BLUEBOOK && c2->getTag() == Tag::BALL) {
		//下雨
		rain->setPosition(s1->getPosition());
		addChild(rain);
		//星光
		galaxy->setPosition(s1->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);
		s1->removeFromParentAndCleanup(true);
		//道具效果
		level2::Bluefunc();
		ball->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c2->getTag() == Tag::BLUEBOOK && c1->getTag() == Tag::BALL) {
		rain->setPosition(s2->getPosition());
		addChild(rain);

		galaxy->setPosition(s2->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);

		//道具效果
		level2::Bluefunc();

		s2->removeFromParentAndCleanup(true);
		ball->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c1->getTag() == Tag::SHIP && c2->getTag() == Tag::BALL ||
		c2->getTag() == Tag::SHIP && c1->getTag() == Tag::BALL) {
		GameOver();
	}

	return true;
}



void level2::GameOver() {

	//排行榜
	if (_scorevalue > Fifth&&_scorevalue <= Fourth) {
		database->setIntegerForKey("FIFTH_PLACE2", _scorevalue);
		database->flush();
	}
	else if (_scorevalue > Fourth&&_scorevalue <= Third) {
		database->setIntegerForKey("FIFTH_PLACE2", Fourth);
		database->setIntegerForKey("FOURTH_PLACE2", _scorevalue);
		database->flush();
	}
	else if (_scorevalue > Third&&_scorevalue <= Second) {
		database->setIntegerForKey("FIFTH_PLACE2", Fourth);
		database->setIntegerForKey("FOURTH_PLACE2", Third);
		database->setIntegerForKey("THIRD_PLACE2", _scorevalue);
		database->flush();
	}
	else if (_scorevalue > Second&&_scorevalue <= First) {
		database->setIntegerForKey("FIFTH_PLACE2", Fourth);
		database->setIntegerForKey("FOURTH_PLACE2", Third);
		database->setIntegerForKey("THIRD_PLACE2", Second);
		database->setIntegerForKey("SECOND_PLACE2", _scorevalue);
		database->flush();
	}
	else if (_scorevalue > First) {
		database->setIntegerForKey("FIFTH_PLACE2", Fourth);
		database->setIntegerForKey("FOURTH_PLACE2", Third);
		database->setIntegerForKey("THIRD_PLACE2", Second);
		database->setIntegerForKey("SECOND_PLACE2", First);
		database->setIntegerForKey("FIRST_PLACE2", _scorevalue);
		database->flush();
	}

	_eventDispatcher->removeAllEventListeners();

	ball->getPhysicsBody()->setVelocity(Vec2(0, 0));

	player->getPhysicsBody()->setVelocity(Vec2(0, 0));

	SimpleAudioEngine::getInstance()->stopBackgroundMusic("bgm.mp3");

	SimpleAudioEngine::getInstance()->playEffect("gameover.mp3", false);

	auto GO_bg = Sprite::create("btn.png");
	GO_bg->setScale(2, 4);
	GO_bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
	this->addChild(GO_bg, 10);

	if (_scorevalue < target_score) {
		auto label1 = LabelTTF::create("Game Over~", "STXINWEI", 60);

		label1->setColor(Color3B(2, 0, 0));

		label1->setPosition(visibleSize.width / 2, visibleSize.height / 2);

		this->addChild(label1, 11);

		auto label2 = Label::createWithTTF("重玩", "fonts/STXINWEI.TTF", 40);

		label2->setColor(Color3B(2, 0, 0));

		auto replayBtn = MenuItemLabel::create(label2, CC_CALLBACK_1(level2::replayCallback, this));

		Menu* replay = Menu::create(replayBtn, NULL);

		replay->setPosition(visibleSize.width / 2 - 90, visibleSize.height / 2 - 100);

		this->addChild(replay, 11);

		auto label3 = Label::createWithTTF("退出", "fonts/STXINWEI.TTF", 40);

		label3->setColor(Color3B(2, 0, 0));

		auto exitBtn = MenuItemLabel::create(label3, CC_CALLBACK_1(level2::exitCallback, this));

		Menu* exit = Menu::create(exitBtn, NULL);

		exit->setPosition(visibleSize.width / 2 + 90, visibleSize.height / 2 - 100);

		this->addChild(exit, 11);
	}
	else if (_scorevalue >= target_score) {

		auto label1 = LabelTTF::create("Congratulations!", "STXINWEI", 60);

		label1->setColor(Color3B(2, 0, 0));

		label1->setPosition(visibleSize.width / 2, visibleSize.height / 2);

		this->addChild(label1, 11);

		auto label2 = Label::createWithTTF("重玩", "fonts/STXINWEI.TTF", 40);

		label2->setColor(Color3B(2, 0, 0));

		auto replayBtn = MenuItemLabel::create(label2, CC_CALLBACK_1(level2::replayCallback, this));

		Menu* replay = Menu::create(replayBtn, NULL);

		replay->setPosition(visibleSize.width / 2 - 120, visibleSize.height / 2 - 100);

		this->addChild(replay, 11);


		//下一关按钮
		auto label4 = Label::createWithTTF("下一关", "fonts/STXINWEI.TTF", 40);
		label4->setColor(Color3B(2, 0, 0));
		auto nextBtn = MenuItemLabel::create(label4, CC_CALLBACK_1(level2::nextCallback, this));
		Menu* next = Menu::create(nextBtn, NULL);
		next->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 100);
		this->addChild(next, 11);

		//退出按钮
		auto label3 = Label::createWithTTF("退出", "fonts/STXINWEI.TTF", 40);

		label3->setColor(Color3B(2, 0, 0));

		auto exitBtn = MenuItemLabel::create(label3, CC_CALLBACK_1(level2::exitCallback, this));

		Menu* exit = Menu::create(exitBtn, NULL);

		exit->setPosition(visibleSize.width / 2 + 120, visibleSize.height / 2 - 100);

		this->addChild(exit, 11);
	}



	//返回按钮
	auto labelS = Label::create("Return", "fonts/STXINWEI.TTF", 30);
	labelS->setColor(Color3B(2, 0, 0));
	auto exitbtnS = MenuItemLabel::create(labelS, CC_CALLBACK_1(level2::returnMenu, this));
	Menu* exitS = Menu::create(exitbtnS, NULL);
	exitS->setPosition(Vec2(visibleSize.width*0.9, visibleSize.height*0.955));
	this->addChild(exitS, 12);

}



// 继续或重玩按钮响应函数



void level2::replayCallback(Ref * pSender) {
	Director::getInstance()->replaceScene(HitBrick::createScene());
}


//返回前一场景
void level2::returnMenu(Ref* pSender) {
	Director::getInstance()->replaceScene(mode_choose::createScene());
}


void level2::nextCallback(Ref * pSender) {
	Director::getInstance()->pushScene(level3::createScene());
}

// 退出
void level2::exitCallback(Ref * pSender) {
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}



void level2::Redfunc() {
	Vec2 velocity = ball->getPhysicsBody()->getVelocity();
	ball->getPhysicsBody()->setVelocity(0.75*velocity);
}


void level2::Bluefunc() {
	onBig = true;
}