#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
#include "MapCreator.h"

USING_NS_CC;

class GameManager :public Node 
{
public:

	static GameManager* create(int num);
	bool init(int num);
	void update(float delta);

	void dispGoal();

	MapCreator* map;
	bool* isGoal;

	float timer;

};


#endif // !__GAME_MANAGER_H__
