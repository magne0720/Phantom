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
	DrawNode* draw;
	Color4F myColor;

public:
	static Goal* create(Vec2 spawnPos,Color4F color);
	virtual bool init(Vec2 spawnPos,Color4F color);
	void update(float delta);

	Color4F getStageColor();
	float getAnimationScale();
	void stopAnimation();

};

#endif // !__GOAL_H__
