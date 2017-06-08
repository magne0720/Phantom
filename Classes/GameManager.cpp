#include "GameManager.h"

GameManager* GameManager::create(int num)
{
	GameManager *pRet = new GameManager();
	if (pRet && pRet->init(num))
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


bool GameManager::init(int num) 
{
	if (!Node::init())return false;

	map = MapCreator::create(num);
	addChild(map);

	isGoal = &map->robot->isGoal;

	timer = 0;


	scheduleUpdate();


	return true;
};

void GameManager::update(float delta) 
{
	if (*isGoal)
	{
		if (timer == 0) {
			dispGoal();
			timer = 1;
		}
	}
};

void GameManager::dispGoal()
{
	Sprite* sp = Sprite::create("sphere.png");
	sp->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f));
	addChild(sp);

	RotateBy* rotate = RotateBy::create(2, 360);
	sp->runAction(RepeatForever::create(rotate));

	log("goal");

};
