#pragma once

#include "cocos2d.h"					

using namespace std;

USING_NS_CC;


class GameMenu : public cocos2d::Layer



{

public:    static Scene* createScene();



		   virtual bool init();



		   CREATE_FUNC(GameMenu);



		   void EnterHitBrick(Ref *pSender);

		   void EnterSet(Ref *pSender);

		   void EnterHelp(Ref *pSender);
};

