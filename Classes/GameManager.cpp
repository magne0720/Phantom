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
	messageSp->setPosition(Vec2(designResolutionSize.width*0.75f, designResolutionSize.height*-0.1f));
	messageSp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	addChild(messageSp);

	messageLabel = Label::create("","fonts/arial.ttf",120);
	messageLabel->setPosition(Vec2(designResolutionSize.width*0.75f, designResolutionSize.height*-0.1f));
	messageLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	addChild(messageLabel);

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
			if (timer > 10.0f)
			{
				StayShowMessage();
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
		//CallFunc* ClearLabel = CallFunc::create([&]() {
		//	for (int i = 0; i < 30; i++) {
		//		CharacterAnimation* CA = CharacterAnimation::create("Character/TitleAnim.png", Size(250, 250));
		//		CA->setPosition(designResolutionSize*0.5f);
		//		addChild(CA);
		//		//MoveBy* move = MoveBy::create(2, Vec2(random(-1000, 1000), random(-1000, 1000)));
		//		MoveBy* move = MoveBy::create(1, Vec2(0, 200));
		//		FadeOut* out = FadeOut::create(1);
		//		Spawn* fech2 = Spawn::createWithTwoActions(move, out);
		//		CA->getSp()->runAction(fech2);
		//	}
		//});
		DelayTime* delay = DelayTime::create(1.0f);
		MoveTo* move = MoveTo::create(1, Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f));
		ScaleTo*scale = ScaleTo::create(1, 50);
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
		sp->runAction(Sequence::create(rTo, sZoomIn, sZoomOut, out, nullptr));
	}
	timer += 1.0 / 60.0f;
	if (timer > 2.5f) {

		map->robot->scheduleUpdate();

		timer = 0;
		return true;
	}


	return false;
};

void GameManager::StayShowMessage() 
{
	messageLabel->stopAllActions();
	messageSp->stopAllActions();
	MoveTo* moveUpL = MoveTo::create(1, Vec2(designResolutionSize.width*0.75f, designResolutionSize.height*0.1f));
	messageLabel->runAction(moveUpL);
	MoveTo* moveUpS = MoveTo::create(1, Vec2(designResolutionSize.width*0.75f, designResolutionSize.height*0.1f));
	messageSp->runAction(moveUpS);
};

void GameManager::StayCloseMessage() 
{
	messageLabel->stopAllActions();
	messageSp->stopAllActions();
	MoveTo* moveUpL = MoveTo::create(1, Vec2(designResolutionSize.width*0.75f, designResolutionSize.height*-0.1f));
	messageLabel->runAction(moveUpL);
	MoveTo* moveUpS = MoveTo::create(1, Vec2(designResolutionSize.width*0.75f, designResolutionSize.height*-0.1f));
	messageSp->runAction(moveUpS);
};

