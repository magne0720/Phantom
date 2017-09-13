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
	// �Ώۂ̃C�x���g�����s���ꂽ��A���ʂ̃C�x���g�͔�������Ȃ�����
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

	animationCount = START_COUNT;
	timer = 0;
	gameState = GAMESTATE::SANDBY;

	messageSp = Sprite::create("Game/Message/MessageBox_1.png");
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

	map->robot->rightRobot->goal = map->goal;
	map->robot->leftRobot->goal = map->goal;

	map->robot->rightRobot->goalPa->setParticleColor(stageColor);
	map->robot->leftRobot->goalPa->setParticleColor(stageColor);
/*
	map->robot->rightRobot->myPosition = map->goal->getPosition();
*/
	SimpleAudioEngine::getInstance()->preloadEffect("Sounds/GameClear.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Sounds/GameStart.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Sounds/PlayerLife.mp3");
	SimpleAudioEngine::getInstance()->playEffect("Sounds/GameStart.mp3");


	scheduleUpdate();

	return true;
};

void GameManager::update(float delta)
{
	if (*isGoal)gameState = GAMESTATE::CLEAR;
	switch (gameState)
	{
	case SANDBY:
		//�Q�[�����n�܂�����
		if (standbyAnimation())
			gameState = GAMESTATE::PLAY;
		break;
	case PLAY:
		//�v���C���[�̋O�������߂Ă��鎞
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
			//�J�E���g�_�E�����ɍs�����L�����Z�������Ƃ��ɖ߂�
		if (!map->robot->rightRobot->isStandby || !map->robot->leftRobot->isStandby)
		{
			timer = 0;
			animationCount = START_COUNT;
			gameState = GAMESTATE::PLAY;
			break;
		}
		//�v���C���[���n�߂鎞
		if (startAnimation())
		{
			map->robot->startRobot();
			gameState = GAMESTATE::MOVING;
			map->robot->rightRobot->isNext = true;
			map->robot->leftRobot->isNext = true;
		}
		break;
	case MOVING:
		if (!map->robot->rightRobot->isStandby&&!map->robot->leftRobot->isStandby) 
		{
			gameState = GAMESTATE::MOVE_STOP;
			playerLife--;
		}
		break;
	case MOVE_STOP:
		//�v���C���[�������̂��~�߂���
		if (stopAnimation())
		{
			dispLife(playerLife, maxLife);
			map->robot->rightRobot->messageSp->setVisible(false);
			map->robot->leftRobot->messageSp->setVisible(false);
			if (playerLife == 0)
				gameState = GAMESTATE::MISS;
			else {
				gameState = GAMESTATE::PLAY;
			}
		}
		break;
	case CLEAR:
		//�N���A������
		dispGoal();
		break;
	case MISS:
		//���ׂĂ̍s���񐔂��Ȃ����Ă��܂�����
		missAnimation();
		break;
	default:
		break;
	}
};

//���C�t�̕\��
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
		map->goal->setZOrder(7);

		//�f�[�^�̕ۑ�
		user->saveClear(map->getLevel());
		user->saveLastClear(map->getLevel());
		user->savePlayerColor(stageColor);

		//map->goal->stopAnimation();


		//���C�t�����R�ɏ���
		for (int i = 0; i < lifeSps.size(); i++) {
			MoveBy* mMove = MoveBy::create(1.0f, Vec2(0, 200));
			FadeOut* mFade = FadeOut::create(1.0f);
			Spawn* mFech = Spawn::createWithTwoActions(mMove, mFade);
			lifeSps.at(i)->runAction(mFech);
		}

		//�S�[���̃A�j���[�V����
		CallFunc* goSelect = CallFunc::create([&]()
		{
			Director::getInstance()->replaceScene(TitleSelectScene::createSelectScene(map->goal->getStageColor()));
		});
		//���̍Đ�
		CallFunc* goSound = CallFunc::create([&]()
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/GameClear.mp3");
		});
		//�X�e�[�W�ɉ��������o
		CallFunc* goSprite = CallFunc::create([&]()
		{
			checkGoalSprite();
		});


		DelayTime* delay = DelayTime::create(1.0f);
		MoveTo* move = MoveTo::create(1, Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f));
		ScaleTo*scale = ScaleTo::create(2, 70);
		DelayTime* labelDelay = DelayTime::create(5.0f);
		//�N���A�����F�ɉ������A�C�e��


		map->goal->runAction(Sequence::create(delay, goSound, move, scale,goSprite,labelDelay, goSelect, nullptr));
		/*
			RotateBy* rotate = RotateBy::create(2, 360);
			clipp->runAction(RepeatForever::create(rotate));
		*/
	}
};

void GameManager::checkGoalSprite() 
{
	Sprite* spSrc;
	Sprite* spMask;
	BlendFunc negativeBlend = { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };
	
	switch ((eColor)map->getLevel())
	{
	case eColor::RED://�Ԃ̐F
	{
		spSrc = Sprite::create("Game/Clear/Red.png");
		spSrc->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.4f));
		spSrc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		spSrc->setScaleY(0);
		addChild(spSrc);
		spSrc->runAction(
			Sequence::create(ScaleTo::create(0.3f, 1, 1.2), ScaleTo::create(0.1f, 1, 1), DelayTime::create(1.0f),
				Spawn::createWithTwoActions(MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(1.0f)), nullptr));
		spMask = Sprite::create("Game/Clear/Red_mask.png");
		spMask->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.4f));
		spMask->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		spMask->setScaleY(0);
		spMask->setScaleY(0);
		addChild(spMask);
		spMask->runAction(
			Sequence::create(ScaleTo::create(0.3f, 1, 1.2), ScaleTo::create(0.1f, 1, 1), FadeOut::create(1.0f),
				Spawn::createWithTwoActions(MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(1.0f)), nullptr));
	}
	break;
	case eColor::SKY://�󂪕ω�
	{
		spSrc = Sprite::create("Game/Clear/Sky.png");
		spSrc->setPosition(Vec2(designResolutionSize.width*0.0f, designResolutionSize.height*0.5f));
		spSrc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		addChild(spSrc);
		spSrc->runAction(
			Sequence::create(MoveTo::create(2.0f,Vec2(designResolutionSize.width*2.0f,designResolutionSize.height*0.5f)), nullptr));
	}
		break;
	case eColor::PURPLE://���傤����
	{
		spSrc = Sprite::create("Game/Clear/Purple.png");
		spSrc->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.4f));
		spSrc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		spSrc->setScaleY(0);
		addChild(spSrc);
		spSrc->runAction(
			Sequence::create(ScaleTo::create(0.3f, 1, 1.2), ScaleTo::create(0.1f, 1, 1), DelayTime::create(1.0f),
				Spawn::createWithTwoActions(MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(1.0f)), nullptr));
		spMask = Sprite::create("Game/Clear/Purple_mask.png");
		spMask->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.4f));
		spMask->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		spMask->setScaleY(0);
		spMask->setScaleY(0);
		addChild(spMask);
		spMask->runAction(
			Sequence::create(ScaleTo::create(0.3f, 1, 1.2), ScaleTo::create(0.1f, 1, 1), FadeOut::create(1.0f),
				Spawn::createWithTwoActions(MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(1.0f)), nullptr));
	}
		break;
	case eColor::GREEN://���S��
	{
		spSrc = Sprite::create("Game/Clear/Green.png");
		spSrc->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.1f));
		spSrc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		spSrc->setScaleY(0);
		addChild(spSrc);
		spSrc->runAction(
			Sequence::create(ScaleTo::create(0.3f, 1, 1.2), ScaleTo::create(0.1f, 1, 1), DelayTime::create(1.0f),
				Spawn::createWithTwoActions(MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(1.0f)), nullptr));
		spMask = Sprite::create("Game/Clear/Green_mask.png");
		spMask->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.1f));
		spMask->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		spMask->setScaleY(0);
		spMask->setScaleY(0);
		addChild(spMask);
		spMask->runAction(
			Sequence::create(ScaleTo::create(0.3f, 1, 1.2), ScaleTo::create(0.1f, 1, 1), FadeOut::create(1.0f),
				Spawn::createWithTwoActions(MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(1.0f)), nullptr));
	}
		break;
	case eColor::ORANGE://�󂪕ω�
	{
		spSrc = Sprite::create("Game/Clear/Sky.png");
		spSrc->setPosition(Vec2(designResolutionSize.width*0.0f, designResolutionSize.height*0.5f));
		spSrc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		addChild(spSrc);
		spSrc->runAction(
			Sequence::create(MoveTo::create(2.0f, Vec2(designResolutionSize.width*2.0f, designResolutionSize.height*0.5f)), nullptr));
	}
		break;
	case eColor::BROWN://�؂̊�
	{
		spSrc = Sprite::create("Game/Clear/Brown.png");
		spSrc->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.1f));
		spSrc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		spSrc->setScaleY(0);
		addChild(spSrc);
		spSrc->runAction(
			Sequence::create(ScaleTo::create(0.3f, 1, 1.2), ScaleTo::create(0.1f, 1, 1), DelayTime::create(1.0f),
				Spawn::createWithTwoActions(MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(1.0f)), nullptr));
		spMask = Sprite::create("Game/Clear/Brown_mask.png");
		spMask->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.1f));
		spMask->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		spMask->setScaleY(0);
		spMask->setScaleY(0);
		addChild(spMask);
		spMask->runAction(
			Sequence::create(ScaleTo::create(0.3f, 1, 1.2), ScaleTo::create(0.1f, 1, 1), FadeOut::create(1.0f),
				Spawn::createWithTwoActions(MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(1.0f)), nullptr));
	}
		break;
	case eColor::BLUE://���傤����
	{
		spSrc = Sprite::create("Game/Clear/Purple.png");
		spSrc->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.4f));
		spSrc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		spSrc->setScaleY(0);
		addChild(spSrc);
		spSrc->runAction(
			Sequence::create(ScaleTo::create(0.3f, 1, 1.2), ScaleTo::create(0.1f, 1, 1), DelayTime::create(1.0f),
				Spawn::createWithTwoActions(MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(1.0f)), nullptr));
		spMask = Sprite::create("Game/Clear/Purple_mask.png");
		spMask->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.4f));
		spMask->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		spMask->setScaleY(0);
		spMask->setScaleY(0);
		addChild(spMask);
		spMask->runAction(
			Sequence::create(ScaleTo::create(0.3f, 1, 1.2), ScaleTo::create(0.1f, 1, 1), FadeOut::create(1.0f),
				Spawn::createWithTwoActions(MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(1.0f)), nullptr));
	}
		break;
	case eColor::PINK://�Ԃ̐F
	{
		spSrc = Sprite::create("Game/Clear/Pink.png");
		spSrc->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.4f));
		spSrc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		spSrc->setScaleY(0);
		addChild(spSrc);
		spSrc->runAction(
			Sequence::create(ScaleTo::create(0.3f, 1, 1.2), ScaleTo::create(0.1f, 1, 1), DelayTime::create(1.0f),
				Spawn::createWithTwoActions(MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(1.0f)), nullptr));
		spMask = Sprite::create("Game/Clear/Pink_mask.png");
		spMask->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.4f));
		spMask->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		spMask->setScaleY(0);
		spMask->setScaleY(0);
		addChild(spMask);
		spMask->runAction(
			Sequence::create(ScaleTo::create(0.3f, 1, 1.2), ScaleTo::create(0.1f, 1, 1), FadeOut::create(1.0f),
				Spawn::createWithTwoActions(MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(1.0f)), nullptr));
	}
	break;
	case eColor::INDIGO://�󂪕ω�
	{
		spSrc = Sprite::create("Game/Clear/Sky.png");
		spSrc->setPosition(Vec2(designResolutionSize.width*0.0f, designResolutionSize.height*0.5f));
		spSrc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		addChild(spSrc);
		spSrc->runAction(
			Sequence::create(MoveTo::create(2.0f, Vec2(designResolutionSize.width*2.0f, designResolutionSize.height*0.5f)), nullptr));
	}
		break;
	case eColor::YELLOW://��
	{
		spSrc = Sprite::create("Game/Clear/Star.png");
		spSrc->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.5f));
		spSrc->setOpacity(0);
		addChild(spSrc);
		spSrc->runAction(
			Sequence::create(FadeIn::create(2.0f),DelayTime::create(1.0f),FadeOut::create(1.0f), nullptr));
	}
		break;
	default:
		break;
	}
}

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
	Sprite* sp;
	DelayTime* delay;
	ScaleTo* scaleOut;
	RemoveSelf* remove;
	RotateBy* rTo;
	ScaleTo* sZoomIn;
	ScaleTo* sZoomOut;
	FadeOut* out;

	if (timer == 0)
	{
		switch (animationCount)//�J�E���g�_�E���ɂ���ďo���ԍ���ς���
		{
		case 3:
			sp = Sprite::create("Game/Number/Num_3.png");
			sp->setPosition(designResolutionSize*0.5f);
			addChild(sp);
			delay = DelayTime::create(0.2f);
			out = FadeOut::create(0.5f);
			remove = RemoveSelf::create(true);
			sp->runAction(Sequence::create(delay, out, remove, nullptr));
			break;
		case 2:
			sp = Sprite::create("Game/Number/Num_2.png");
			sp->setPosition(designResolutionSize*0.5f);
			addChild(sp);
			delay = DelayTime::create(0.2f);
			out = FadeOut::create(0.5f);
			remove = RemoveSelf::create(true);
			sp->runAction(Sequence::create(delay, out, remove, nullptr));
			break;
		case 1:
			sp = Sprite::create("Game/Number/Num_1.png");
			sp->setPosition(designResolutionSize*0.5f);
			addChild(sp);
			delay = DelayTime::create(0.2f);
			out = FadeOut::create(0.5f);
			remove = RemoveSelf::create(true);
			sp->runAction(Sequence::create(delay, out, remove, nullptr));
			break;
		case 0:
			sp = Sprite::create("Game/Message/Start.png");
			sp->setPosition(designResolutionSize*0.5f);
			addChild(sp);
			sZoomIn = ScaleTo::create(0.5, 2);
			sZoomOut = ScaleTo::create(0.5, 2);
			out = FadeOut::create(0.5f);
			sp->runAction(Sequence::create(sZoomIn, sZoomOut, out, nullptr));
			break;
		default:
			break;
		}

		sp->setColor(Color3B::Color3B(map->robot->myColor));
	}
	if (timer > 1.0f) {
		if (animationCount == 0) {
			map->robot->scheduleUpdate();

			animationCount = START_COUNT;
			timer = 0;
			return true;
		}
		else 
		{
			animationCount--;
			timer = 0;
			return false;
		}
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
		CallFunc* goSound = CallFunc::create([&]()
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/PlayerLife.mp3");
		}); 
		lifeSps.at(playerLife)->runAction(Sequence::create(delay,sOne,goSound,sZoomTwo,outTwo, nullptr));

	
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
		Sprite* gray = Sprite::create();
		gray->setColor(Color3B::GRAY);
		gray->setTextureRect(Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
		gray->setPosition(designResolutionSize*0.5f);
		addChild(gray);
		BlendFunc screenBlend = { GL_ONE_MINUS_DST_COLOR, GL_ONE };
		gray->setBlendFunc(screenBlend);
		
		FadeIn* fade = FadeIn::create(1.0f);
		gray->runAction(fade);

		Sprite* sp = Sprite::create("Game/Message/Miss.png");
		sp->setPosition(Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*1.2f));
		addChild(sp);

		MoveTo* up = MoveTo::create(1.0f, designResolutionSize*0.5f);
		RotateBy* ro = RotateBy::create(0.5f, -15);

		sp->runAction(Sequence::create(up,ro, nullptr));

		Button* retry = Button::create(0);
		retry->setPosition(Vec2(designResolutionSize.width*0.3f, designResolutionSize.height*0.3f));
		retry->stagenum = map->getLevel();
		retry->color = Color3B(stageColor.r*255.0f,stageColor.g*255.0f,stageColor.b*255.0f);
		retry->setOpacity(0);
		addChild(retry);

		retry->runAction(FadeIn::create(1.0f));

		Button* out = Button::create(1);
		out->setPosition(Vec2(designResolutionSize.width*0.7f, designResolutionSize.height*0.3f));
		out->setOpacity(0);
		addChild(out);

		out->runAction(FadeIn::create(1.0f));


	}
	if (timer < 5.0f) {
		timer += 1.0 / 60.0f;
		return false;
	}else{
		return true;
	}
};

void GameManager::StayShowMessage(int num)
{
	return;
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
	return;
	if (messageSp->getTag() != 1) {
		messageSp->stopAllActions();
		MoveTo* moveUpS = MoveTo::create(1, Vec2(designResolutionSize.width*0.9f, designResolutionSize.height*-0.1f));
		messageSp->runAction(moveUpS);
		messageSp->setTag(1);
	}
};

//�v���C���[�̑��삪�قȂ�̂ŉ��z��
bool GameManager::onTouchBegan(const Touch * touch, Event *unused_event) 
{
	return true;
};

void GameManager::onTouchMoved(const Touch * touch, Event *unused_event)
{
	if (touch->getLocation().x<designResolutionSize.width*0.05f&&
		touch->getLocation().y>designResolutionSize.height*0.95f) 
	{
		timer = 0;
		gameState = GAMESTATE::MISS;
	}
};

void GameManager::onTouchEnded(const Touch * touch, Event *unused_event)
{

};

