#pragma once

#include "cocos2d.h"

using namespace std;

USING_NS_CC;
class HitBrick_Double:public Layer
{
public:
	HitBrick_Double();
	~HitBrick_Double();

	static PhysicsWorld* world;



	static cocos2d::Scene* createScene();



	void setPhysicsWorld(PhysicsWorld * world);



	virtual bool init();

	void BrickGeneraetd();  // 掉落箱子

	void update(float dt);

	void setJoint();

	void addSprite();   // 添加背景和各种精灵



	void addPlayer();   // 添加玩家



	void addListener(); // 添加监听器

	void onKeyPressedL(EventKeyboard::KeyCode code, Event * event);

	void onKeyPressedR(EventKeyboard::KeyCode code, Event * event);
	 
	void onKeyReleasedL(EventKeyboard::KeyCode code, Event * event);

	void onKeyReleasedR(EventKeyboard::KeyCode code, Event * event);

	bool onConcactBegin(PhysicsContact & contact);

	void preloadMusic();                   // 预加载音乐


	 // 游戏结束
	void GameOver();                      

	//左右游戏结束
	void GameOverL();
	void GameOverR();

	void loadAnimation(string filepath); // 加载动画


	// 重玩或退出按钮响应函数



	void replayCallback(Ref * pSender);



	void exitCallback(Ref * pSender);


	
	void returnMenu(Ref* pSengder);
	
	
	//道具函数
	void leftA1();
	void leftA2();
	void leftB();
	void rightA1();
	void rightA2();
	void rightB();


	CREATE_FUNC(HitBrick_Double);

private:

	PhysicsWorld* m_world;



	Size visibleSize;

	Sprite * blackbar;

	Sprite* middlebar;

	Sprite* playerL;

	Sprite* playerR;

	Sprite* ship;

	Sprite* ballL;

	Sprite* ballR;

	// 固定关节


	PhysicsJointPin * jointL;

	PhysicsJointPin * jointR;

	int spHolded;



	int spFactor;


	bool onBall;


	enum Tag { SHIP, LEFTBALL, BOX, LEFTBOARD ,RIGHTBALL,RIGHTBOARD,LEFTRED,LEFTBLUE,RIGHTRED,RIGHTBLUE};

	//左右分数
	int _scorevalueL;
	Label* _scoreLabelL;
	int _scorevalueR;
	Label* _scoreLabelR;

	int dropth;

	int first_drop;


	//道具是否拥有
	bool LeftA1;
	bool LeftA2;
	bool LeftB;
	bool RightA1;
	bool RightA2;
	bool RightB;

	//道具BLUEBOOK
	bool onBigL;
	bool onBigR;
	float bigtimeL;
	float bigtimeR;
	Sprite* bigplayer;

};

