#pragma once
#include"cocos2d.h"

USING_NS_CC;
using namespace std;

class set1:  public  cocos2d::Layer
{
public:
	set1();
	~set1();

	static Scene *createScene();

	virtual bool init();

	void exitSet1(Ref * pSender);

	CREATE_FUNC(set1);

private:
	
	Sprite* background;

	Label* label;
};

