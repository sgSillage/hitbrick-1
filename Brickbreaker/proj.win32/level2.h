

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



	void addSprite();   // ��ӱ����͸��־���



	void addPlayer();   // ������



	void addListener(); // ��Ӽ�����







	void update(float dt);



	void updateReadylong(float dt);  // ���´���ƽ�����



	void BrickGeneraetd();  // ��������







	void onKeyPressed(EventKeyboard::KeyCode code, Event * event);



	void onKeyReleased(EventKeyboard::KeyCode code, Event * event);



	bool onConcactBegin(PhysicsContact & contact);

	void preloadMusic();                   // Ԥ��������



	void GameOver();                      // ��Ϸ����



	void loadAnimation(string filepath); // ���ض���



	//����ʹ�ú���
	void Redfunc();
	void Bluefunc();



	// ������˳���ť��Ӧ����



	void replayCallback(Ref * pSender);



	void exitCallback(Ref * pSender);


	void returnMenu(Ref* pSengder);

	void nextCallback(Ref * pSender);

	// implement the "static create()" method manually



	CREATE_FUNC(level2);

	int _scorevalue;//����

private:



	PhysicsWorld* m_world;



	Size visibleSize;



	Sprite* player;

	Sprite *blackbar;

	Sprite* ship;



	bool onBall;


	//��������
	Sprite* ReadyW;
	Sprite* ReadyB;
	float readylong;
	Sprite* ball;
	Label* ready;
	Label* go;

	// �̶��ؽ�

	PhysicsJointPin * joint1;


	//��������
	int spHolded;
	int spFactor;



	enum Tag { SHIP, BALL, BOX, BOARD, REDBOOK, BLUEBOOK };



	Label* _scoreLabel;

	//Ŀ���
	int target_score;


	//����BLUEBOOK
	bool onBig;
	float bigtime;
	Sprite* bigplayer;


	//���а�
	int First;
	int Second;
	int Third;
	int Fourth;
	int Fifth;
};





