#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
#include "MapCreator.h"

USING_NS_CC;

class GameManager :public Node 
{
public:

	CREATE_FUNC(GameManager);
	bool init();
	void update(float delta);


	MapCreator* map;

	float timer;

};


#endif // !__GAME_MANAGER_H__
