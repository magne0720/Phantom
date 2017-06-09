#include "Goal.h"

Goal* Goal::create(Vec2 spawnPos,Color4F color) 
{
	Goal *pRet = new Goal();
	if (pRet && pRet->init(spawnPos,color))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};
};

bool Goal::init(Vec2 spawnPos,Color4F color) 
{
	if (!Node::init())return false;

	initialize(spawnPos);
	myColor = color;

	draw = DrawNode::create();
	addChild(draw);
	draw->clear();
	draw->drawDot(Vec2(0, 0), animationTimer, color);


	scheduleUpdate();

	return true;
};

void Goal::update(float delta) 
{
	animationTimer += 0.02f;
	if (animationTimer > 1.0f)
		animationTimer = -1.0f;

	draw->clear();
	draw->drawDot(Vec2(0, 0), cos(animationTimer*2.0f)*25.0f+50, myColor);

};

Color4F Goal::getStageColor() 
{
	return myColor;
};

float Goal::getAnimationScale() 
{
	return animationTimer;
};

void Goal::stopAnimation() 
{
	unscheduleUpdate();
};

