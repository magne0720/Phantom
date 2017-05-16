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

	MapCreator* ma = MapCreator::create();
	addChild(ma);
	Layer* layer = ma->printMap();
	addChild(layer);

	scheduleUpdate();

	return true;
};

void MainGameScene::update(float delta)
{
};
