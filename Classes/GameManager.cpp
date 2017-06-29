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

	messageSp = Sprite::create("Game/Message/MessageBox_0.png");
	messageSp->setPosition(Vec2(designResolutionSize.width*0.9f, designResolutionSize.height*-0.1f));
	messageSp->setOpacity(230);
	messageSp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	addChild(messageSp);

	
	maxLife = MAX_LIFE;
	playerLife =maxLife;

	Color4F col = Color4F(user->loadPlayerColor());
	for (int i = 0; i < playerLife; i++) 
	{
		Sprite* sp = Sprite::create("Game/Message/Life.png");
		sp->setColor(Color3B(col.r, col.g, col.b));
		sp->setOpacity(127);
		addChild(sp);
		lifeSps.pushBack(sp);
	}
	dispLife(playerLife,maxLife);

	scheduleUpdate();

	return true;
};

void GameManager::update(float delta)
{

	if (*isGoal)gameState = GAMESTATE::CLEAR;
	switch (gameState)
	{
	case SANDBY:
		//ゲームが始まった時
		if (standbyAnimation())
			gameState = GAMESTATE::PLAY;
		break;
	case PLAY:
		//プレイヤーの軌道を決めている時
		//if (map->robot->rightRobot->isMoveWait || map->robot->leftRobot->isMoveWait)
		//{
		//	StayCloseMessage();
		//	timer = 0;
		//	break;
		//}
		timer += 1.0f / 60.0f;
		{
			if (timer > 8.0f)
			{
				if (messageSp->getTag() == 0)
				{
					StayCloseMessage();
					timer = 0;
					break;
				}
				if ((map->robot->rightRobot->myState == STATUS::FIND) | (map->robot->leftRobot->myState == STATUS::FIND))
				{
					StayShowMessage(2);
					timer = 0;
					break;
				}
				else
				{
					StayShowMessage(1);
					timer = 0;
					break;
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
		if (!map->robot->rightRobot->isMove&&!map->robot->leftRobot->isMove) 
		{
			gameState = GAMESTATE::MOVE_STOP;
			playerLife--;
		}
		break;
	case MOVE_STOP:
		//プレイヤーが歩くのを止めた時
		if (stopAnimation())
		{
			dispLife(playerLife, maxLife);
			map->robot->rightRobot->messageSp->setVisible(false);
			map->robot->leftRobot->messageSp->setVisible(false);
			if (playerLife == 0)
				gameState = GAMESTATE::MISS;
			else {
				map->robot->rightRobot->setState(STATUS::STAND);
				map->robot->leftRobot->setState(STATUS::STAND);
				gameState = GAMESTATE::PLAY;
			}
		}
		break;
	case CLEAR:
		//クリアした時
		dispGoal();
		break;
	case MISS:
		//すべての行動回数をなくしてしまった時
		if (missAnimation()) 
		{
			Director::getInstance()->replaceScene(TitleSelectScene::createSelectScene());
		}
		break;
	default:
		break;
	}
};

//ライフの表示
void GameManager::dispLife(int life,int max) 
{
	for (int i = 0; i < max; i++) 
	{
		lifeSps.at(i)->setPosition(Vec2(designResolutionSize.width*0.1f*i+100, designResolutionSize.height*0.9f));
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
		user->saveLastClear(map->getLevel());
		user->savePlayerColor(stageColor);

		//map->goal->stopAnimation();


		//ライフを自然に消す
		for (int i = 0; i < lifeSps.size(); i++) {
			MoveBy* mMove = MoveBy::create(1.0f, Vec2(0, 200));
			FadeOut* mFade = FadeOut::create(1.0f);
			Spawn* mFech = Spawn::createWithTwoActions(mMove, mFade);
			lifeSps.at(i)->runAction(mFech);
		}

		//ゴールのアニメーション
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
		Sprite* sp = Sprite::create("Game/Message/Start.png");
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
	if (timer == 0)
	{
		Sprite* sp = Sprite::create("Game/Player/StartLogo.png");
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
		DelayTime* delay = DelayTime::create(1.0f);
		ScaleTo* sZoomOne = ScaleTo::create(0.4f, 1.3f);
		FadeIn* outOne = FadeIn::create(0.4f);
		Spawn* sOne = Spawn::createWithTwoActions(sZoomOne, outOne);
		ScaleTo* sZoomTwo = ScaleTo::create(0.5f, 1);
		FadeOut* outTwo = FadeOut::create(0.1f);
		lifeSps.at(playerLife)->runAction(Sequence::create(delay,sOne,sZoomTwo,outTwo, nullptr));
	}
	if (timer > 2.5f) {
		timer = 0;
		return true;
	}
	timer += 1.0 / 60.0f;
	return false;
};

bool GameManager::missAnimation()
{
	if (timer == 0)
	{
		Sprite* sp = Sprite::create("Game/Message/MissLogo.png");
		sp->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*1.2f));
		addChild(sp);

		MoveTo* up = MoveTo::create(1.0f, designResolutionSize*0.5f);
		RotateBy* ro = RotateBy::create(0.5f, -15);


		sp->runAction(Sequence::create(up,ro, nullptr));
	}
	if (timer > 5.0f) {
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
		String* name = String::createWithFormat("Game/Message/MessageBox_%d.png", num);
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

