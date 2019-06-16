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

	void BrickGeneraetd();  // ��������

	void update(float dt);

	void setJoint();

	void addSprite();   // ��ӱ����͸��־���



	void addPlayer();   // ������



	void addListener(); // ��Ӽ�����

	void onKeyPressedL(EventKeyboard::KeyCode code, Event * event);

	void onKeyPressedR(EventKeyboard::KeyCode code, Event * event);
	 
	void onKeyReleasedL(EventKeyboard::KeyCode code, Event * event);

	void onKeyReleasedR(EventKeyboard::KeyCode code, Event * event);

	bool onConcactBegin(PhysicsContact & contact);

	void preloadMusic();                   // Ԥ��������


	 // ��Ϸ����
	void GameOver();                      

	//������Ϸ����
	void GameOverL();
	void GameOverR();

	void loadAnimation(string filepath); // ���ض���


	// ������˳���ť��Ӧ����



	void replayCallback(Ref * pSender);



	void exitCallback(Ref * pSender);


	
	void returnMenu(Ref* pSengder);
	
	
	//���ߺ���
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

	// �̶��ؽ�


	PhysicsJointPin * jointL;

	PhysicsJointPin * jointR;

	int spHolded;



	int spFactor;


	bool onBall;


	enum Tag { SHIP, LEFTBALL, BOX, LEFTBOARD ,RIGHTBALL,RIGHTBOARD,LEFTRED,LEFTBLUE,RIGHTRED,RIGHTBLUE};

	//���ҷ���
	int _scorevalueL;
	Label* _scoreLabelL;
	int _scorevalueR;
	Label* _scoreLabelR;

	int dropth;

	int first_drop;


	//�����Ƿ�ӵ��
	bool LeftA1;
	bool LeftA2;
	bool LeftB;
	bool RightA1;
	bool RightA2;
	bool RightB;

	//����BLUEBOOK
	bool onBigL;
	bool onBigR;
	float bigtimeL;
	float bigtimeR;
	Sprite* bigplayer;

};

