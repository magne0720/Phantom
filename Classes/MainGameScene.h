#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "cocos2d.h"
#include "AllTags.h"
#include "Character.h"
#include "PlayerHuman.h"
#include "PlayerDog.h"
#include "PlayerPhantom.h"

USING_NS_CC;

class MainGameScene :public Scene 
{
public:
	static MainGameScene* createScene(int num);
	bool init(int num);

	

};

#endif //!__MAIN_GAME_SCENE_H__

