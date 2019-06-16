#pragma once
#include "cocos2d.h"

USING_NS_CC;
class mode_choose:public Layer
{
public:
	mode_choose();
	~mode_choose();

	static Scene* createScene();

	virtual bool init();

	void solomode(Ref* pSender);

	void pkmode(Ref* pSender);

	void returnMenu(Ref* pSengder);

	CREATE_FUNC(mode_choose);

};

