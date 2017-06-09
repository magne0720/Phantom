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
	stageColor = map->goals.at(0)->getStageColor();

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
	map->goals.at(0)->stopAnimation();
	CallFunc* goSelect = CallFunc::create([&]()
	{
		Director::getInstance()->replaceScene(TitleSelectScene::createSelectScene());
	});
	MoveTo* move=MoveTo::create(2, Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f));
	ScaleTo*scale = ScaleTo::create(5,50);
	map->goals.at(0)->runAction(Sequence::create(move,scale,goSelect,nullptr));
/*
	RotateBy* rotate = RotateBy::create(2, 360);
	clipp->runAction(RepeatForever::create(rotate));
*/
	log("goal");

};
