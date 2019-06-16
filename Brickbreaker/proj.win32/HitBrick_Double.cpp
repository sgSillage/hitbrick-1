#include "HitBrick_Double.h"

#include "cocos2d.h"

#include "mode_choose.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

void HitBrick_Double::setPhysicsWorld(PhysicsWorld* world) { m_world = world; }

HitBrick_Double::HitBrick_Double(){}


HitBrick_Double::~HitBrick_Double(){}


Scene* HitBrick_Double::createScene() {
	srand((unsigned)time(NULL));

	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setAutoStep(true);

	// Debug 模式


	// scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setGravity(Vec2(0, -300.0f));

	auto layer = HitBrick_Double::create();

	layer->setPhysicsWorld(scene->getPhysicsWorld());
	layer->setJoint();
	scene->addChild(layer);

	return scene;
}


bool HitBrick_Double::init()
{

	if (!Layer::init()) {
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	auto edgeSp = Sprite::create();  //创建一个精灵

	auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 1.0f, 0.0f), 3);  //edgebox是不受刚体碰撞影响的一种刚体，我们用它来设置物理世界的边界

	edgeSp->setPosition(visibleSize.width / 2, visibleSize.height / 2);  //位置设置在屏幕中央

	edgeSp->setPhysicsBody(boundBody);

	addChild(edgeSp);

	//小球
	auto box = Sprite::create("box.png");
	int xbox = box->getContentSize().width; int ybox = box->getContentSize().height;

	//左边分数
	auto score_btnL = Sprite::create("btn.png");
	score_btnL->setScale(0.7, 0.5);
	score_btnL->setAnchorPoint(Vec2(0, 0.7));
	score_btnL->setPosition(Vec2(15, visibleSize.height));
	this->addChild(score_btnL, 10);
	_scoreLabelL = Label::createWithSystemFont("Score:00", "fonts/arial.ttf", 32);
	_scoreLabelL->setPosition(100, visibleSize.height * 0.955);
	this->addChild(_scoreLabelL, 21);
	_scorevalueL = 0;
	//右边分数
	auto score_btnR = Sprite::create("orangebar.png");
	score_btnR->setScale(0.7, 0.5);
	score_btnR->setAnchorPoint(Vec2(0, 0.7));
	score_btnR->setPosition(Vec2(visibleSize.width*0.5 + 15, visibleSize.height));
	this->addChild(score_btnR, 19);
	_scoreLabelR = Label::createWithSystemFont("Score:00", "fonts/arial.ttf", 32);
	_scoreLabelR->setPosition(visibleSize.width*0.5 + 100, visibleSize.height * 0.955);
	this->addChild(_scoreLabelR, 22);
	_scorevalueR = 0;
	

	//返回按钮
	auto labelF = Label::create("Return", "fonts/STXINWEI.TTF", 30);
	labelF->setColor(Color3B(2, 0, 0));
	auto exitbtnF = MenuItemLabel::create(labelF, CC_CALLBACK_1(HitBrick_Double::returnMenu, this));
	auto exitF = Menu::create(exitbtnF, NULL);
	exitF->setPosition(Vec2(visibleSize.width*0.9, visibleSize.height*0.955));
	this->addChild(exitF, 12);
	preloadMusic(); // 预加载音效

	addSprite();    // 添加背景和各种精灵

	addListener();  // 添加监听器 

	addPlayer();    // 添加球与板

	BrickGeneraetd();  // 生成砖块

	schedule(schedule_selector(HitBrick_Double::update), 0.01f, kRepeatForever, 0.1f);

	onBall = true;

	spHolded = -1;

	spFactor = 0;

	dropth = 0;

	first_drop = -1;

	LeftA1 = false;
	LeftA2 = false;
	LeftB = false;
	RightA1 = false;
	RightA2 = false;
	RightB = false;

	onBigL = false;
	onBigR = false;
	bigtimeL = bigtimeR = 0;

	return true;
}

void HitBrick_Double::setJoint()
{
	Vec2 jointLpoint = Vec2(ballL->getAnchorPoint().x, ballL->getAnchorPoint().y - 30);

	Vec2 jointRpoint = Vec2(ballR->getAnchorPoint().x, ballR->getAnchorPoint().y - 30);

	jointL = PhysicsJointPin::construct(ballL->getPhysicsBody(), playerL->getPhysicsBody(), jointLpoint, playerL->getAnchorPoint());

	jointR = PhysicsJointPin::construct(ballR->getPhysicsBody(), playerR->getPhysicsBody(), jointRpoint, playerR->getAnchorPoint());

	m_world->addJoint(jointL);
	m_world->addJoint(jointR);
}




//预加载音效


void HitBrick_Double::preloadMusic() {

	auto sae = SimpleAudioEngine::getInstance();

	sae->preloadEffect("gameover.mp3");

	sae->preloadBackgroundMusic("bgm.mp3");

	sae->playBackgroundMusic("bgm.mp3", true);
}


//添加背景和各种精灵

void HitBrick_Double::addSprite()
{
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

	//add middle bar

	middlebar = Sprite::create("blackbar.png");

	middlebar->setScale((visibleSize.height - 100) / middlebar->getContentSize().width, 0.2);

	middlebar->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));

	auto rotate = RotateBy::create(0.1, 90);

	middlebar->runAction(rotate);

	auto midbody = PhysicsBody::createBox(middlebar->getContentSize(), PhysicsMaterial(1000.0f, 1.0f, 10.0f));

	midbody->setCategoryBitmask(0xFFFFFFFF);

	midbody->setCollisionBitmask(0xFFFFFFFF);

	midbody->setContactTestBitmask(0xFFFFFFFF);

	midbody->setTag(3);

	midbody->setGravityEnable(false);

	midbody->setDynamic(false);

	middlebar->setPhysicsBody(midbody);

	this->addChild(middlebar, 2);
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



void HitBrick_Double::addListener() {
	//左边玩家监听器
	auto keyboardListenerL = EventListenerKeyboard::create();

	keyboardListenerL->onKeyPressed = CC_CALLBACK_2(HitBrick_Double::onKeyPressedL, this);

	keyboardListenerL->onKeyReleased = CC_CALLBACK_2(HitBrick_Double::onKeyReleasedL, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListenerL, this);
	//右边玩家监听器
	auto keyboardListenerR = EventListenerKeyboard::create();

	keyboardListenerR->onKeyPressed = CC_CALLBACK_2(HitBrick_Double::onKeyPressedR, this);
	
	keyboardListenerR->onKeyReleased = CC_CALLBACK_2(HitBrick_Double::onKeyReleasedR, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListenerR, this);
	//碰撞检测监听器
	auto contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(HitBrick_Double::onConcactBegin, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}


//创建左右两个玩家

void HitBrick_Double::addPlayer()
{
	//左边玩家
	playerL = Sprite::create("bar.png");
	int xpos = visibleSize.width / 2;

	playerL->setScale(0.1f, 0.1f);

	playerL->setPosition(Vec2(xpos*0.5, ship->getContentSize().height - playerL->getContentSize().height*0.1f));

	// 设置左边板的刚体属性
	// Todo
	auto playerLBody = PhysicsBody::createBox(playerL->getContentSize(), PhysicsMaterial(1000.0f, 1.0f, 10.0f));

	playerLBody->setCategoryBitmask(0xFFFFFFFF);

	playerLBody->setCollisionBitmask(0xFFFFFFFF);

	playerLBody->setContactTestBitmask(0xFFFFFFFF);

	playerLBody->setGravityEnable(false);

	playerLBody->setTag(Tag::LEFTBOARD);

	playerL->setPhysicsBody(playerLBody);

	playerL->getPhysicsBody()->setRotationEnable(false);

	this->addChild(playerL, 2);

	ballL = Sprite::create("ball.png");

	ballL->setPosition(Vec2(xpos*0.5, playerL->getPosition().y + ballL->getContentSize().height*0.1f));

	ballL->setScale(0.1f, 0.1f);

	// 设置球的刚体属性
	// Todo
	auto ballLBody = PhysicsBody::createCircle(ballL->getContentSize().height / 2, PhysicsMaterial(0.1f, 1.0f, 0.0f));

	ballLBody->setCategoryBitmask(0xFFFFFFFF);

	ballLBody->setCollisionBitmask(0xFFFFFFFF);

	ballLBody->setContactTestBitmask(0xFFFFFFFF);

	ballLBody->setGravityEnable(false);

	ballLBody->setTag(Tag::LEFTBALL);

	ballLBody->setRotationEnable(false);

	ballL->setPhysicsBody(ballLBody);

	addChild(ballL, 3);
	//右边玩家
	playerR = Sprite::create("bar.png");

	playerR->setScale(0.1f, 0.1f);

	playerR->setPosition(Vec2(xpos*1.5, ship->getContentSize().height - playerR->getContentSize().height*0.1f));

	// 设置右边板的刚体属性
	// Todo
	auto playerRBody = PhysicsBody::createBox(playerR->getContentSize(), PhysicsMaterial(1000.0f, 1.0f, 10.0f));

	playerRBody->setCategoryBitmask(0xFFFFFFFF);

	playerRBody->setCollisionBitmask(0xFFFFFFFF);

	playerRBody->setContactTestBitmask(0xFFFFFFFF);

	playerRBody->setGravityEnable(false);

	playerRBody->setTag(Tag::RIGHTBOARD);

	playerR->setPhysicsBody(playerRBody);

	playerR->getPhysicsBody()->setRotationEnable(false);

	this->addChild(playerR, 2);

	ballR = Sprite::create("ball.png");

	ballR->setPosition(Vec2(xpos*1.5, playerR->getPosition().y + ballR->getContentSize().height*0.1f));

	ballR->setScale(0.1f, 0.1f);

	// 设置右边球的刚体属性
	// Todo
	auto ballRBody = PhysicsBody::createCircle(ballR->getContentSize().height / 2, PhysicsMaterial(0.1f, 1.0f, 0.0f));

	ballRBody->setCategoryBitmask(0xFFFFFFFF);

	ballRBody->setCollisionBitmask(0xFFFFFFFF);

	ballRBody->setContactTestBitmask(0xFFFFFFFF);

	ballRBody->setGravityEnable(false);

	ballRBody->setTag(Tag::RIGHTBALL);

	ballRBody->setRotationEnable(false);

	ballR->setPhysicsBody(ballRBody);

	addChild(ballR, 3);
}

void HitBrick_Double::update(float dt) {
	//左边玩家板的界限
	if (playerL->getPosition().x < 100) {
		playerL->setPosition(100, playerL->getPosition().y);
		playerL->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
	else if (playerL->getPosition().x > visibleSize.width*0.5 - 100)
	{
		playerL->setPosition(visibleSize.width*0.5 - 100, playerL->getPosition().y);
		playerL->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
	//右边玩家板的界限
	if (playerR->getPosition().x < visibleSize.width*0.5 + 100) {
		playerR->setPosition(visibleSize.width*0.5 + 100, playerR->getPosition().y);
		playerR->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
	else if (playerR->getPosition().x > visibleSize.width - 100)
	{
		playerR->setPosition(visibleSize.width - 100, playerR->getPosition().y);
		playerR->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
	
	if (_scorevalueL == 2250 || _scorevalueR == 2250) {
		ballL->getPhysicsBody()->setVelocity(Vec2(0, 0));

		playerL->getPhysicsBody()->setVelocity(Vec2(0, 0));

		ballR->getPhysicsBody()->setVelocity(Vec2(0, 0));

		playerR->getPhysicsBody()->setVelocity(Vec2(0, 0));

		GameOver();
	}
	//蓄力
	if (spHolded == 1 && spFactor <= 30)
		spFactor++;

	//BLUEBOOK部分
	if (onBigL && bigtimeL == 0) {
		//道具所用板
		bigplayer = Sprite::create("bar.png");
		bigplayer->setScale(visibleSize.width / bigplayer->getContentSize().width*0.5, 0.1f);
		bigplayer->setPosition(Vec2(visibleSize.width*0.25, ship->getContentSize().height - bigplayer->getContentSize().height*0.1f + 50));

		// 设置板的刚体属性
		// Todo
		auto playerBody = PhysicsBody::createBox(bigplayer->getContentSize(), PhysicsMaterial(1000.0f, 1.0f, 10.0f));

		playerBody->setCategoryBitmask(0xFFFFFFFF);

		playerBody->setCollisionBitmask(0xFFFFFFFF);

		playerBody->setContactTestBitmask(0xFFFFFFFF);

		playerBody->setGravityEnable(false);

		playerBody->setTag(Tag::LEFTBOARD);

		playerBody->setDynamic(false);

		bigplayer->setPhysicsBody(playerBody);

		bigplayer->getPhysicsBody()->setRotationEnable(false);

		this->addChild(bigplayer, 2);
		bigtimeL++;
	}
	else if (onBigL) {
		bigtimeL++;
		if (bigtimeL >= 300) {
			bigtimeL += 0;
			bigplayer->removeFromParentAndCleanup(true);
			onBigL = false;
		}
	}

	//BLUEBOOK部分
	if (onBigR && bigtimeR == 0) {
		//道具所用板
		bigplayer = Sprite::create("bar.png");
		bigplayer->setScale(visibleSize.width / bigplayer->getContentSize().width*0.5, 0.1f);
		bigplayer->setPosition(Vec2(visibleSize.width*0.75, ship->getContentSize().height - bigplayer->getContentSize().height*0.1f + 50));

		// 设置板的刚体属性
		// Todo
		auto playerBody = PhysicsBody::createBox(bigplayer->getContentSize(), PhysicsMaterial(1000.0f, 1.0f, 10.0f));

		playerBody->setCategoryBitmask(0xFFFFFFFF);

		playerBody->setCollisionBitmask(0xFFFFFFFF);

		playerBody->setContactTestBitmask(0xFFFFFFFF);

		playerBody->setGravityEnable(false);

		playerBody->setTag(Tag::RIGHTBOARD);

		playerBody->setDynamic(false);

		bigplayer->setPhysicsBody(playerBody);

		bigplayer->getPhysicsBody()->setRotationEnable(false);

		this->addChild(bigplayer, 2);
		bigtimeR++;
	}
	else if (onBigR) {
		bigtimeR++;
		if (bigtimeR >= 300) {
			bigtimeR += 0;
			bigplayer->removeFromParentAndCleanup(true);
			onBigR = false;
		}
	}
}

//添加砖块   

void HitBrick_Double::BrickGeneraetd() {
	for (int i = 1; i < 5; i++) {
		int cw = 30;
		while (cw <= visibleSize.width) {
			// 为砖块设置刚体属性
			// Todo
			if (cw == 585) {
				auto box = Sprite::create("box.png");
				cw += box->getContentSize().width;
				cw += box->getContentSize().width;
			}
			if (cw == 400 && i == 3) {
				auto box = Sprite::create("redbook.png");

				box->setPosition(cw, visibleSize.height - box->getContentSize().height * (i + 1));

				cw += box->getContentSize().width;

				auto boxBody = PhysicsBody::createCircle(box->getContentSize().height / 2, PhysicsMaterial(100.0f, 1.0f, 0.0f));

				boxBody->setCategoryBitmask(0xFFFFFFFF);

				boxBody->setCollisionBitmask(0xFFFFFFFF);

				boxBody->setContactTestBitmask(0xFFFFFFFF);

				boxBody->setGravityEnable(false);

				boxBody->setTag(Tag::LEFTRED);

				boxBody->setDynamic(false);

				box->setPhysicsBody(boxBody);

				box->getPhysicsBody()->setRotationEnable(false);

				addChild(box, 4);
			}
			
			else if (cw == 104 && i == 3) {
				auto box = Sprite::create("redbook.png");

				box->setPosition(cw, visibleSize.height - box->getContentSize().height * (i + 1));

				cw += box->getContentSize().width;

				auto boxBody = PhysicsBody::createCircle(box->getContentSize().height / 2, PhysicsMaterial(100.0f, 1.0f, 0.0f));

				boxBody->setCategoryBitmask(0xFFFFFFFF);

				boxBody->setCollisionBitmask(0xFFFFFFFF);

				boxBody->setContactTestBitmask(0xFFFFFFFF);

				boxBody->setGravityEnable(false);

				boxBody->setTag(Tag::LEFTRED);

				boxBody->setDynamic(false);

				box->setPhysicsBody(boxBody);

				box->getPhysicsBody()->setRotationEnable(false);

				addChild(box, 4);
			}

			else if (cw == 215 && i == 4) {
				auto box = Sprite::create("bluebook.png");

				box->setPosition(cw, visibleSize.height - box->getContentSize().height * (i + 1));

				cw += box->getContentSize().width;

				auto boxBody = PhysicsBody::createCircle(box->getContentSize().height / 2, PhysicsMaterial(100.0f, 1.0f, 0.0f));

				boxBody->setCategoryBitmask(0xFFFFFFFF);

				boxBody->setCollisionBitmask(0xFFFFFFFF);

				boxBody->setContactTestBitmask(0xFFFFFFFF);

				boxBody->setGravityEnable(false);

				boxBody->setTag(Tag::LEFTBLUE);

				boxBody->setDynamic(false);

				box->setPhysicsBody(boxBody);

				box->getPhysicsBody()->setRotationEnable(false);

				addChild(box, 4);
			}

			else if (cw == 733 && i == 3) {
				auto box = Sprite::create("redbook.png");

				box->setPosition(cw, visibleSize.height - box->getContentSize().height * (i + 1));

				cw += box->getContentSize().width;

				auto boxBody = PhysicsBody::createCircle(box->getContentSize().height / 2, PhysicsMaterial(100.0f, 1.0f, 0.0f));

				boxBody->setCategoryBitmask(0xFFFFFFFF);

				boxBody->setCollisionBitmask(0xFFFFFFFF);

				boxBody->setContactTestBitmask(0xFFFFFFFF);

				boxBody->setGravityEnable(false);

				boxBody->setTag(Tag::RIGHTRED);

				boxBody->setDynamic(false);

				box->setPhysicsBody(boxBody);

				box->getPhysicsBody()->setRotationEnable(false);

				addChild(box, 4);
			}

			else if (cw == 1029 && i == 3) {
			auto box = Sprite::create("redbook.png");

			box->setPosition(cw, visibleSize.height - box->getContentSize().height * (i + 1));

			cw += box->getContentSize().width;

			auto boxBody = PhysicsBody::createCircle(box->getContentSize().height / 2, PhysicsMaterial(100.0f, 1.0f, 0.0f));

			boxBody->setCategoryBitmask(0xFFFFFFFF);

			boxBody->setCollisionBitmask(0xFFFFFFFF);

			boxBody->setContactTestBitmask(0xFFFFFFFF);

			boxBody->setGravityEnable(false);

			boxBody->setTag(Tag::RIGHTRED);

			boxBody->setDynamic(false);

			box->setPhysicsBody(boxBody);

			box->getPhysicsBody()->setRotationEnable(false);

			addChild(box, 4);
			}

			else if (cw == 844 && i == 4) {
			auto box = Sprite::create("bluebook.png");

			box->setPosition(cw, visibleSize.height - box->getContentSize().height * (i + 1));

			cw += box->getContentSize().width;

			auto boxBody = PhysicsBody::createCircle(box->getContentSize().height / 2, PhysicsMaterial(100.0f, 1.0f, 0.0f));

			boxBody->setCategoryBitmask(0xFFFFFFFF);

			boxBody->setCollisionBitmask(0xFFFFFFFF);

			boxBody->setContactTestBitmask(0xFFFFFFFF);

			boxBody->setGravityEnable(false);

			boxBody->setTag(Tag::RIGHTBLUE);

			boxBody->setDynamic(false);

			box->setPhysicsBody(boxBody);

			box->getPhysicsBody()->setRotationEnable(false);

			addChild(box, 4);
			}

			else {
			auto box = Sprite::create("box.png");

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

void HitBrick_Double::onKeyPressedR(EventKeyboard::KeyCode code, Event* event) {

	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (playerR->getPosition().x > visibleSize.width *0.5 + 100) {
			playerR->getPhysicsBody()->setVelocity(Vec2(-500, 0));
		}
		else {
			//playerR->setPosition(visibleSize.width *0.5 +100, playerR->getPosition().y);
			playerR->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		// 左右移动
		// Todo
		if (playerR->getPosition().x < visibleSize.width - 100) {
			playerR->getPhysicsBody()->setVelocity(Vec2(500, 0));
		}
		else {
			//playerR->setPosition(visibleSize.width-100,playerR->getPosition().y);
			playerR->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_1:
		if (RightA1 || RightA2) {
			HitBrick_Double::rightA1();
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_2:
		if (RightA1 || RightA2) {
			HitBrick_Double::rightA2();
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_3:
		if (RightB) {
			HitBrick_Double::rightB();
		}break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE: // 开始蓄力
		if (spHolded == -1)
			spHolded = 1;
		break;
	default:
		break;
	}
}

void HitBrick_Double::onKeyPressedL(EventKeyboard::KeyCode code, Event* event)
{
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		if (playerL->getPosition().x > 100) {
			playerL->getPhysicsBody()->setVelocity(Vec2(-500, 0));
		}
		else {
			//playerL->setPosition(100, playerL->getPosition().y);
			playerL->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		break;
		
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		if (playerL->getPosition().x < visibleSize.width*0.5 - 100) {
			playerL->getPhysicsBody()->setVelocity(Vec2(500, 0));
		}
		else {
			//playerL->setPosition(visibleSize.width *0.5 - 100, playerL->getPosition().y);
			playerL->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		if (LeftA1 || LeftA2) {
			HitBrick_Double::leftA1();
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_K:
		if (LeftA1 || LeftA2) {
			HitBrick_Double::leftA2();
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_L:
		if (LeftB) {
			HitBrick_Double::leftB();
		}
		break;
	default:
		break;
	}
}


void HitBrick_Double::onKeyReleasedR(EventKeyboard::KeyCode code, Event* event) {
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		// 停止运动
		// Todo
		playerR->getPhysicsBody()->setVelocity(Vec2(0, 0));
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:   // 蓄力结束，小球发射
		if (spHolded == 1) {
			spHolded = 0;
			m_world->removeJoint(jointR);
			m_world->removeJoint(jointL);

			ballR->getPhysicsBody()->setVelocity(Vec2(0, spFactor * 30));
			ballL->getPhysicsBody()->setVelocity(Vec2(0, spFactor * 30));
		}
		break;
	default:
		break;
	}
}

void HitBrick_Double::onKeyReleasedL(EventKeyboard::KeyCode code, Event* event) {
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		// 停止运动
		// Todo
		playerL->getPhysicsBody()->setVelocity(Vec2(0, 0));
		break;
	default:
		break;
	}
}



// 碰撞检测
// Todo
bool HitBrick_Double::onConcactBegin(PhysicsContact & contact) {
	auto c1 = contact.getShapeA()->getBody(), c2 = contact.getShapeB()->getBody();

	auto s1 = (Sprite*)c1->getNode(), s2 = (Sprite*)c2->getNode();

	auto rain = ParticleRain::create();
	auto galaxy = ParticleGalaxy::create();

	auto rotate1 = RotateBy::create(0.5, 60);
	auto rotate2 = RotateBy::create(0.5, 30);

	if (c1->getTag() == Tag::BOX && c2->getTag() == Tag::LEFTBALL) {
		//下雨
		rain->setPosition(s1->getPosition());
		addChild(rain);
		//星光
		galaxy->setPosition(s1->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);
		s1->removeFromParentAndCleanup(true);
		//分数
		_scoreLabelL->setString(StringUtils::format("Score:%i", _scorevalueL += 50));

		ballL->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c2->getTag() == Tag::BOX && c1->getTag() == Tag::LEFTBALL) {
		rain->setPosition(s2->getPosition());
		addChild(rain);

		galaxy->setPosition(s2->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);

		_scoreLabelL->setString(StringUtils::format("Score:%i", _scorevalueL += 50));

		s2->removeFromParentAndCleanup(true);
		ballL->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c1->getTag() == Tag::BOX && c2->getTag() == Tag::RIGHTBALL) {
		//下雨
		rain->setPosition(s1->getPosition());
		addChild(rain);
		//星光
		galaxy->setPosition(s1->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);
		s1->removeFromParentAndCleanup(true);
		//分数
		_scoreLabelR->setString(StringUtils::format("Score:%i", _scorevalueR += 50));

		ballR->runAction(Sequence::create(rotate1, rotate2, NULL));
	}
	
	else if (c2->getTag() == Tag::BOX && c1->getTag() == Tag::RIGHTBALL) {
		rain->setPosition(s2->getPosition());
		addChild(rain);

		galaxy->setPosition(s2->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);

		_scoreLabelR->setString(StringUtils::format("Score:%i", _scorevalueR += 50));

		s2->removeFromParentAndCleanup(true);
		ballR->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c1->getTag() == Tag::LEFTRED && c2->getTag() == Tag::LEFTBALL) {
		//下雨
		rain->setPosition(s1->getPosition());
		addChild(rain);
		//星光
		galaxy->setPosition(s1->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);
		s1->removeFromParentAndCleanup(true);

		if (!LeftA1) { LeftA1 = true; }
		else if (!LeftA2) { LeftA2 = true; }

		ballL->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c2->getTag() == Tag::LEFTRED && c1->getTag() == Tag::LEFTBALL) {
		rain->setPosition(s2->getPosition());
		addChild(rain);

		galaxy->setPosition(s2->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);

		if (!LeftA1) { LeftA1 = true; }
		else if (!LeftA2) { LeftA2 = true; }

		s2->removeFromParentAndCleanup(true);
		ballL->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c1->getTag() == Tag::LEFTBLUE && c2->getTag() == Tag::LEFTBALL) {
		//下雨
		rain->setPosition(s1->getPosition());
		addChild(rain);
		//星光
		galaxy->setPosition(s1->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);
		s1->removeFromParentAndCleanup(true);

		if (!LeftB) { LeftB = true; }
		
		ballL->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c2->getTag() == Tag::LEFTBLUE && c1->getTag() == Tag::LEFTBALL) {
		rain->setPosition(s2->getPosition());
		addChild(rain);

		galaxy->setPosition(s2->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);

		if (!LeftB) { LeftB = true; }

		s2->removeFromParentAndCleanup(true);
		ballL->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c1->getTag() == Tag::RIGHTRED && c2->getTag() == Tag::RIGHTBALL) {
		//下雨
		rain->setPosition(s1->getPosition());
		addChild(rain);
		//星光
		galaxy->setPosition(s1->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);
		s1->removeFromParentAndCleanup(true);

		if (!RightA1) { RightA1 = true; }
		else if(!RightA2) { RightA2 = true; }

		ballR->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c2->getTag() == Tag::RIGHTRED && c1->getTag() == Tag::RIGHTBALL) {
		rain->setPosition(s2->getPosition());
		addChild(rain);

		galaxy->setPosition(s2->getPosition());
		galaxy->setDuration(1.0f);
		addChild(galaxy);

		if (!RightA1) { RightA1 = true; }
		else if (!RightA2) { RightA2 = true; }

		s2->removeFromParentAndCleanup(true);
		ballR->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c1->getTag() == Tag::RIGHTBLUE && c2->getTag() == Tag::RIGHTBALL) {
	//下雨
	rain->setPosition(s1->getPosition());
	addChild(rain);
	//星光
	galaxy->setPosition(s1->getPosition());
	galaxy->setDuration(1.0f);
	addChild(galaxy);
	s1->removeFromParentAndCleanup(true);

	if (!RightB) { RightB = true; }

	ballR->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c2->getTag() == Tag::RIGHTBLUE && c1->getTag() == Tag::RIGHTBALL) {
	rain->setPosition(s2->getPosition());
	addChild(rain);

	galaxy->setPosition(s2->getPosition());
	galaxy->setDuration(1.0f);
	addChild(galaxy);

	if (!RightB) { RightB = true; }

	s2->removeFromParentAndCleanup(true);
	ballR->runAction(Sequence::create(rotate1, rotate2, NULL));
	}

	else if (c1->getTag() == Tag::SHIP && c2->getTag() == Tag::LEFTBALL ||
		c2->getTag() == Tag::SHIP && c1->getTag() == Tag::LEFTBALL) {
		dropth++;
		GameOverL();
	}

	else if (c1->getTag() == Tag::SHIP && c2->getTag() == Tag::RIGHTBALL ||
		c2->getTag() == Tag::SHIP && c1->getTag() == Tag::RIGHTBALL) {
		dropth++;
		GameOverR();
	}

	return true;
}

void HitBrick_Double::GameOverL() {
	ballL->getPhysicsBody()->setVelocity(Vec2(0, 0));

	playerL->getPhysicsBody()->setVelocity(Vec2(0, 0));

	first_drop = 0;
	if (dropth == 2)
		GameOver();
}

void HitBrick_Double::GameOverR() {
	ballR->getPhysicsBody()->setVelocity(Vec2(0, 0));

	playerR->getPhysicsBody()->setVelocity(Vec2(0, 0));

	first_drop = 1;

	if (dropth == 2)
		GameOver();
}

void HitBrick_Double::GameOver() {
	_eventDispatcher->removeAllEventListeners();

	SimpleAudioEngine::getInstance()->stopBackgroundMusic("bgm.mp3");

	SimpleAudioEngine::getInstance()->playEffect("gameover.mp3", false);

	auto GO_bg = Sprite::create("btn.png");
	GO_bg->setScale(2, 4);
	GO_bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
	this->addChild(GO_bg, 5);

	if (_scorevalueL > _scorevalueR) {
		auto label1 = LabelTTF::create("Winner:\nLeft player", "STXINWEI", 60,
			Size(visibleSize.width/3,200),CCTextAlignment::CENTER);

		label1->setColor(Color3B(2, 0, 0));

		label1->setPosition(visibleSize.width / 2, visibleSize.height / 2);

		this->addChild(label1, 11);
	}

	else if (_scorevalueL < _scorevalueR) {
		auto label1 = LabelTTF::create("Winner:\nRight player", "STXINWEI", 60,
			Size(visibleSize.width / 3, 200), CCTextAlignment::CENTER);

		label1->setColor(Color3B(2, 0, 0));

		label1->setPosition(visibleSize.width / 2, visibleSize.height / 2 );

		this->addChild(label1, 11);
	}

	else if (_scorevalueL = _scorevalueR && first_drop == 0) {
		auto label1 = LabelTTF::create("Winner:\nRight player", "STXINWEI", 60,
			Size(visibleSize.width / 3, 200), CCTextAlignment::CENTER);

		label1->setColor(Color3B(2, 0, 0));

		label1->setPosition(visibleSize.width / 2, visibleSize.height / 2);

		this->addChild(label1, 11);
	}

	else if (_scorevalueL = _scorevalueR && first_drop == 1) {
		auto label1 = LabelTTF::create("Winner:\nLeft player", "STXINWEI", 60,
			Size(visibleSize.width / 3, 200), CCTextAlignment::CENTER);

		label1->setColor(Color3B(2, 0, 0));

		label1->setPosition(visibleSize.width / 2, visibleSize.height / 2);

		this->addChild(label1, 11);
	}

	else {
		auto label1 = LabelTTF::create("NO Winner!", "STXINWEI", 60,
			Size(visibleSize.width / 3, 200), CCTextAlignment::CENTER);

		label1->setColor(Color3B(2, 0, 0));

		label1->setPosition(visibleSize.width / 2, visibleSize.height / 2-100);

		this->addChild(label1, 11);
	}

	auto label2 = Label::createWithTTF("Replay", "fonts/STXINWEI.TTF", 40);

	label2->setColor(Color3B(2, 0, 0));

	auto replayBtn = MenuItemLabel::create(label2, CC_CALLBACK_1(HitBrick_Double::replayCallback, this));

	Menu* replay = Menu::create(replayBtn, NULL);

	replay->setPosition(visibleSize.width / 2 - 90, visibleSize.height / 2 - 100);

	this->addChild(replay, 11);

	auto label3 = Label::createWithTTF("Exit", "fonts/STXINWEI.TTF", 40);

	label3->setColor(Color3B(2, 0, 0));

	auto exitBtn = MenuItemLabel::create(label3, CC_CALLBACK_1(HitBrick_Double::exitCallback, this));

	Menu* exit = Menu::create(exitBtn, NULL);

	exit->setPosition(visibleSize.width / 2 + 90, visibleSize.height / 2 - 100);

	this->addChild(exit,11);

	//返回按钮
	auto labelS = Label::create("Return", "fonts/STXINWEI.TTF", 30);
	labelS->setColor(Color3B(2, 0, 0));
	auto exitbtnS = MenuItemLabel::create(labelS, CC_CALLBACK_1(HitBrick_Double::returnMenu, this));
	Menu* exitS = Menu::create(exitbtnS, NULL);
	exitS->setPosition(Vec2(visibleSize.width*0.9, visibleSize.height*0.955));
	this->addChild(exitS, 12);

}

void HitBrick_Double::replayCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(HitBrick_Double::createScene());
}

//返回前一场景
void HitBrick_Double::returnMenu(Ref* pSender) {
	Director::getInstance()->replaceScene(mode_choose::createScene());
}

void HitBrick_Double::exitCallback(Ref * pSender) {
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void HitBrick_Double::leftA1() {
	Vec2 velocity = ballL->getPhysicsBody()->getVelocity();
	ballL->getPhysicsBody()->setVelocity(0.75*velocity);
}

void HitBrick_Double::leftA2() {
	Vec2 velocity = ballR->getPhysicsBody()->getVelocity();
	ballR->getPhysicsBody()->setVelocity(1.5*velocity);
}


void HitBrick_Double::rightA1() {
	Vec2 velocity = ballR->getPhysicsBody()->getVelocity();
	ballR->getPhysicsBody()->setVelocity(0.75*velocity);
}


void HitBrick_Double::rightA2() {
	Vec2 velocity = ballL->getPhysicsBody()->getVelocity();
	ballL->getPhysicsBody()->setVelocity(1.5*velocity);
}

void HitBrick_Double::leftB() {
	onBigL = true;
}

void HitBrick_Double::rightB() {
	onBigR = true;
}