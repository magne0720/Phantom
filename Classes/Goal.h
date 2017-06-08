#ifndef __GOAL_H__
#define __GOAL_H__

#include "cocos2d.h"
#include"ObjectBase.h"

USING_NS_CC;

//ìGÇÃäÓñ{évçl
class Goal :public ObjectBase 
{
private:
	float animationTimer;


public:
	static Goal* create(Vec2 spawnPos);
	virtual bool init(Vec2 spawnPos);
	void update(float delta);

	

};

#endif // !__GOAL_H__
