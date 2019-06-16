

#include "cocos2d.h"

using namespace std;

USING_NS_CC;

class level2 : public Layer {



public:



	static PhysicsWorld* world;



	static Scene* createScene();



	void setPhysicsWorld(PhysicsWorld * world);



	virtual bool init();



	void setJoint();



	void addSprite();   // 添加背景和各种精灵



	void addPlayer();   // 添加玩家



	void addListener(); // 添加监听器







	void update(float dt);



	void updateReadylong(float dt);  // 更新船的平衡情况



	void BrickGeneraetd();  // 掉落箱子







	void onKeyPressed(EventKeyboard::KeyCode code, Event * event);



	void onKeyReleased(EventKeyboard::KeyCode code, Event * event);



	bool onConcactBegin(PhysicsContact & contact);

	void preloadMusic();                   // 预加载音乐



	void GameOver();                      // 游戏结束



	void loadAnimation(string filepath); // 加载动画



	//道具使用函数
	void Redfunc();
	void Bluefunc();



	// 重玩或退出按钮响应函数



	void replayCallback(Ref * pSender);



	void exitCallback(Ref * pSender);


	void returnMenu(Ref* pSengder);

	void nextCallback(Ref * pSender);

	// implement the "static create()" method manually



	CREATE_FUNC(level2);

	int _scorevalue;//分数

private:



	PhysicsWorld* m_world;



	Size visibleSize;



	Sprite* player;

	Sprite *blackbar;

	Sprite* ship;



	bool onBall;


	//蓄力进度
	Sprite* ReadyW;
	Sprite* ReadyB;
	float readylong;
	Sprite* ball;
	Label* ready;
	Label* go;

	// 固定关节

	PhysicsJointPin * joint1;


	//蓄力所用
	int spHolded;
	int spFactor;



	enum Tag { SHIP, BALL, BOX, BOARD, REDBOOK, BLUEBOOK };



	Label* _scoreLabel;

	//目标分
	int target_score;


	//道具BLUEBOOK
	bool onBig;
	float bigtime;
	Sprite* bigplayer;


	//排行榜
	int First;
	int Second;
	int Third;
	int Fourth;
	int Fifth;
};





