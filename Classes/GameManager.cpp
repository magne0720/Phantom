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
	stageColor = map->goal->getStageColor();

	user = SaveData::create();
	addChild(user);
	log("%d", user->loadClear());

	timer = 0;
	isGoalAnimation = false;
	gameState = GAMESTATE::SANDBY;

	messageSp = Sprite::create("MessageBox.png");
	messageSp->setPosition(Vec2(designResolutionSize.width*0.9f, designResolutionSize.height*-0.1f));
	messageSp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	addChild(messageSp);

	scheduleUpdate();

	return true;
};

void GameManager::update(float delta)
{
	switch (gameState)
	{
	case SANDBY:
		if (standbyAnimation())
			gameState = GAMESTATE::PLAY;
		break;
	case PLAY:
		timer += 1.0f / 60.0f;
		{
			if (timer > 6.0f)
			{
				if (map->robot->rightRobot->myState == STATUS::FIND | map->robot->leftRobot->myState == STATUS::FIND) 
				{
					StayShowMessage(2);
				}
				else 
				{
					StayShowMessage(1);
				}
				timer = 0;
			}
			else
			{
				if (map->robot->rightRobot->isPut||map->robot->leftRobot->isPut)
				{
					StayCloseMessage();
					timer = 0;
				}
			}
			if (map->robot->rightRobot->isStart&&map->robot->leftRobot->isStart)gameState = GAMESTATE::MOVING;
			if (*isGoal)gameState = GAMESTATE::CLEAR;
		}
		break;
	case MOVING:
		if (!map->robot->rightRobot->isStart&&!map->robot->leftRobot->isStart)gameState = GAMESTATE::PLAY;
		if (*isGoal)gameState = GAMESTATE::CLEAR;
		break;
	case CLEAR:
		dispGoal();
		break;
	case MISS:
		break;
	default:
		break;
	}
};

void GameManager::dispGoal()
{
	if (map->goal->drawGoalAction()) {
		//map->goal->stopAnimation();
		unscheduleUpdate();
		/*DrawNode* circle = DrawNode::create();
		addChild(circle);
		circle->drawDot(Vec2(0,0), map->goal->getAnimationScale()+50, map->goal->getStageColor());
	*/

		user->saveClear(map->getLevel());
		//map->goal->stopAnimation();
		CallFunc* goSelect = CallFunc::create([&]()
		{
			Director::getInstance()->replaceScene(TitleSelectScene::createSelectScene(map->goal->getStageColor()));
		});
		DelayTime* delay = DelayTime::create(1.0f);
		MoveTo* move = MoveTo::create(1, Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f));
		ScaleTo*scale = ScaleTo::create(2, 70);
		DelayTime* labelDelay = DelayTime::create(1.0f);

		map->goal->runAction(Sequence::create(delay, move, scale,labelDelay, goSelect, nullptr));
		/*
			RotateBy* rotate = RotateBy::create(2, 360);
			clipp->runAction(RepeatForever::create(rotate));
		*/
	}
};

bool GameManager::standbyAnimation() 
{
	if (timer == 0) 
	{
		Sprite* sp = Sprite::create("StartLogo.png");
		sp->setPosition(designResolutionSize*0.5f);
		addChild(sp);
		RotateBy* rTo = RotateBy::create(1, 360);
		ScaleTo* sZoomIn = ScaleTo::create(0.5, 2);
		ScaleTo* sZoomOut = ScaleTo::create(0.5, 2);
		FadeOut* out = FadeOut::create(0.5f);
		sp->runAction(Sequence::create(sZoomIn,rTo ,sZoomOut, out, nullptr));
	}
	timer += 1.0 / 60.0f;
	if (timer > 2.5f) {

		map->robot->scheduleUpdate();

		timer = 0;
		return true;
	}


	return false;
};

void GameManager::StayShowMessage(int num) 
{
	String* name = String::createWithFormat("MessageBox_%d.png", num);

	messageSp->setTexture(name->getCString());
	messageSp->stopAllActions();
	MoveTo* moveUpS = MoveTo::create(1, Vec2(designResolutionSize.width*0.9f, designResolutionSize.height*0.1f));
	messageSp->runAction(moveUpS);
};

void GameManager::StayCloseMessage() 
{
	messageSp->stopAllActions();
	MoveTo* moveUpS = MoveTo::create(1, Vec2(designResolutionSize.width*0.9f, designResolutionSize.height*-0.1f));
	messageSp->runAction(moveUpS);
};
