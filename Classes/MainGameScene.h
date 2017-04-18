#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "cocos2d.h"
#include "AllTags.h"
#include "Character.h"
#include "PlayerHuman.h"
#include "PlayerDog.h"
#include "PlayerPhantom.h"
#include "Enemy.h"

USING_NS_CC;

class MainGameScene :public Scene 
{
public:
	static MainGameScene* createScene(int num);
	bool init(int num);
	void update(float delta);
	
	PlayerPhantom* p;
	Enemy* enemy;
};

#endif //!__MAIN_GAME_SCENE_H__

