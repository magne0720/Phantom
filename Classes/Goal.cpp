#include "Goal.h"

Goal* Goal::create(Vec2 spawnPos) 
{
	Goal *pRet = new Goal();
	if (pRet && pRet->init(spawnPos))
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

bool Goal::init(Vec2 spawnPos) 
{
	if (!Node::init())return false;

	initialize(spawnPos);

	mySprite = CharacterAnimation::createInMove("goal.png",Size(100,100));
	addChild(mySprite);

	Sprite* sp = Sprite::create("goal.png");
	addChild(sp);

	//scheduleUpdate();

	return true;
};

void Goal::update(float delta) 
{

}
