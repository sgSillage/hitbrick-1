#pragma once
#include"cocos2d.h"

USING_NS_CC;
class Help:public Layer
{
public:
	Help();
	~Help();

	static Scene *createScene();

	virtual bool init();

	CREATE_FUNC(Help);

	void exitHelp(Ref *pSender);

private:
	Sprite* background;

	Label* label;
};

