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
	p = PlayerPhantom::create(Vec2(designResolutionSize.width*0.3f, designResolutionSize.height*0.8f),
		Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.2f));
	addChild(p);

	enemy = Enemy::create(Vec2(designResolutionSize.width*0.5f,designResolutionSize.height*0.5f),DIR_DEGREE::DIR_RIGHT);
	addChild(enemy);

	scheduleUpdate();

	return true;
};

void MainGameScene::update(float delta) 
{
	enemy->checkPlayer(p->pHuman->myPosition);
	enemy->onCollision(p->pHuman->myPosition, p->pDog->myPosition);
};
