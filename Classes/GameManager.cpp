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

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->onTouchBegan = CC_CALLBACK_2(GameManager::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameManager::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameManager::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	user = SaveData::create();
	addChild(user);
	//log("%d", user->loadClear());

	map = MapCreator::create(num,user->loadPlayerColor());
	addChild(map);

	isGoal = &map->robot->isGoal;
	stageColor = map->goal->getStageColor();

	playerCount = 5;
	timer = 0;
	isGoalAnimation = false;
	gameState = GAMESTATE::SANDBY;

	messageSp = Sprite::create("MessageBox_0.png");
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
		//ゲームが始まった時
		if (standbyAnimation())
			gameState = GAMESTATE::PLAY;
		break;
	case PLAY:
		//プレイヤーの軌道を決めている時
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
			if (map->robot->rightRobot->isStandby&&map->robot->leftRobot->isStandby) 
			{
				StayCloseMessage();
				timer = 0;
				gameState = GAMESTATE::MOVE_START;
			}
		}
		break;
	case MOVE_START:
		//プレイヤーが始める時
		if (startAnimation())
		{
			map->robot->startRobot();
			gameState = GAMESTATE::MOVING;
		}
		break;
	case MOVING:
		if (!map->robot->rightRobot->isStart&&!map->robot->leftRobot->isStart)gameState = GAMESTATE::MOVE_STOP;
		if (*isGoal)gameState = GAMESTATE::CLEAR;
		break;
	case MOVE_STOP:
		//プレイヤーが歩くのを止めた時
		if (stopAnimation())
			gameState = GAMESTATE::PLAY;
		break;
	case CLEAR:
		//クリアした時
		dispGoal();
		break;
	case MISS:
		//すべての行動回数をなくしてしまった時
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

		//データの保存
		user->saveClear(map->getLevel());
		user->savePlayerColor(stageColor);
		checkTime();

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

void GameManager::checkTime()
{
	switch (map->getLevel())
	{
	case TIME_ZONE::MORNING:
		user->saveTimeZone(TIME_ZONE::MORNING);
		user->saveStarAppear(false);
		break;
	case TIME_ZONE::EVENING:
		user->saveTimeZone(TIME_ZONE::EVENING);
		user->saveStarAppear(false);
		break;
	case TIME_ZONE::NIGHT:
		user->saveTimeZone(TIME_ZONE::NIGHT);
		user->saveStarAppear(false);
		break;
	case TIME_ZONE::STAR:
		user->saveStarAppear(true);
		break;
	default:
		break;
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
	if (timer > 2.5f) {

		map->robot->scheduleUpdate();

		timer = 0;
		return true;
	}
	timer += 1.0 / 60.0f;
	return false;
};

bool GameManager::startAnimation() 
{
	log("start");
	if (timer == 0)
	{
		Sprite* sp = Sprite::create("StartLogo.png");
		sp->setPosition(designResolutionSize*0.5f);
		addChild(sp);
		RotateBy* rTo = RotateBy::create(1, 360);
		ScaleTo* sZoomIn = ScaleTo::create(0.5, 2);
		ScaleTo* sZoomOut = ScaleTo::create(0.5, 2);
		FadeOut* out = FadeOut::create(0.5f);
		sp->runAction(Sequence::create(sZoomIn, rTo, sZoomOut, out, nullptr));
	}
	if (timer > 2.5f) {

		map->robot->scheduleUpdate();

		timer = 0;
		return true;
	}
	timer += 1.0 / 60.0f;
	return false;
};

bool GameManager::stopAnimation()
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
		sp->runAction(Sequence::create(sZoomIn, rTo, sZoomOut, out, nullptr));
	}
	if (timer > 2.5f) {
		timer = 0;
		return true;
	}
	timer += 1.0 / 60.0f;
	return false;
};


void GameManager::StayShowMessage(int num)
{
	if (messageSp->getTag() != 0) 
	{
		String* name = String::createWithFormat("MessageBox_%d.png", num);
		messageSp->setTexture(name->getCString());
		messageSp->stopAllActions();
		MoveTo* moveUpS = MoveTo::create(1, Vec2(designResolutionSize.width*0.9f, designResolutionSize.height*0.1f));
		messageSp->runAction(moveUpS);
		messageSp->setTag(0);
	}
};

void GameManager::StayCloseMessage() 
{
	if (messageSp->getTag() != 1) {
		messageSp->stopAllActions();
		MoveTo* moveUpS = MoveTo::create(1, Vec2(designResolutionSize.width*0.9f, designResolutionSize.height*-0.1f));
		messageSp->runAction(moveUpS);
		messageSp->setTag(1);
	}
};

//プレイヤーの操作が異なるので仮想化
bool GameManager::onTouchBegan(const Touch * touch, Event *unused_event) 
{
	return true;
};

void GameManager::onTouchMoved(const Touch * touch, Event *unused_event)
{

};

void GameManager::onTouchEnded(const Touch * touch, Event *unused_event)
{

};

