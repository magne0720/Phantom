#include "MainGameScene.h"


MainGameScene* MainGameScene::createScene(int num)
{
	MainGameScene *pRet = new MainGameScene();
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
	}
};

bool MainGameScene::init(int num) 
{
	if (!Scene::init()) 
	{
		return false;
	}

	gm = GameManager::create(num);
	addChild(gm,0);

	gameLayer = gm->map->printMap();
	addChild(gameLayer,1);

	CharacterAnimation* ap = CharacterAnimation::createInMove("goal.png", Size(100, 100));
	addChild(ap);


	return true;
};
