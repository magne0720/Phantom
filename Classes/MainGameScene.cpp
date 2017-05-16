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
//	p = PlayerPhantom::create(Vec2(designResolutionSize.width*0.3f, designResolutionSize.height*0.8f),
//		Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.2f));
//	addChild(p,3);
//
//	enemy = Enemy::create(Vec2(designResolutionSize.width*0.4f,designResolutionSize.height*0.7f),DIR_DEGREE::DIR_RIGHT);
//	addChild(enemy,2);
//
//	//w = Wall::create(Vec2(designResolutionSize.width*0.7f, designResolutionSize.height*0.6f));
//	//addChild(w,3);
//
//	enemy->setTarget(p->pHuman);
//	enemy->setTarget(p->pDog);
//	/*enemy->setTarget(w);
//	p->pHuman->setTarget(w);
//	p->pDog->setTarget(w);
//*/

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
