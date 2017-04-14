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

	PlayerPhantom* p = PlayerPhantom::create(Vec2(designResolutionSize.width*0.3f, designResolutionSize.height*0.5f),
		Vec2(designResolutionSize.width*0.3f, designResolutionSize.height*0.5f));

	addChild(p);

	return true;
};

