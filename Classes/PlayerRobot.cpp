#include "PlayerRobot.h"

PlayerRobot* PlayerRobot::create(Vec2 pos,Color4F col)
{
	PlayerRobot *pRet = new PlayerRobot();
	if (pRet && pRet->init(pos,col))
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

bool PlayerRobot::init(Vec2 pos,Color4F col)
{
	if (!Node::init())return false;

	SimpleAudioEngine::getInstance()->preloadEffect("Sounds/move_4.mp3");

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// �Ώۂ̃C�x���g�����s���ꂽ��A���ʂ̃C�x���g�͔�������Ȃ�����
	listener->onTouchBegan = CC_CALLBACK_2(PlayerRobot::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerRobot::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerRobot::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	setSpeed(12.0f);
	setGameSpeed(1.0f);
	setMoveRange(100.0f);
	setDoubtDgree(150.0f);
	checkTime = 120.0f;

	initWithFileCenter("Character/TitleAnim.png", Size(250, 250));
	initWithFileCenterB("Character/TitleAnim_Normal.png", Size(250, 250));
	
	messageSp = Sprite::create("PlayerStop.png");
	messageSp->setPosition(Vec2(0, myPosition.y + 50));
	messageSp->setVisible(false);
	addChild(messageSp,25);
	
	startPosition = pos;
	endPosition = pos + Vec2(1, 0);
	initialize(pos, DIR_DEGREE::DIR_RIGHT);

	angleNum = 0;
	isStandby = false;
	setState(STATUS::STAND);

	goalPa = CutParticle::create(20,1, col);
	//goalPa->set
	addChild(goalPa);

	moveRangeSp->drawCircle(Vec2(0, 0), moveRange, 0, 360, false, Color4F::GREEN);

	//�L�����N�^�[�̐F�ω�
	myBlendSprite->getSp()->setColor(Color3B(col.r*255.0f,col.g*255.0f,col.b*255.0f));

	return true;
};

void PlayerRobot::plusAction()
{
		moveTimer+=1.0*gameSpeed;
		switch (myState)
		{
		case STATUS::STAND:
			log("stand");
			if (moveTimer > checkTime / 2)
			{
				moveTimer = 0;
				if (isMove) {
					log("next");
					if (angles.size() > angleNum)
					{
						nextPosition();
					}
					else 
					{
						stopPosition();
					}
				}
			break;
		case STATUS::MOVE:
			//��R�}���ړ�������
			log("move");
			}
			if (onCollision(targets.at(0)->myPosition, moveRange))
			{
				findPosition();
			}
			break;
		case STATUS::STOP:
			log("stop");
			break;
		case STATUS::FIND:
			log("find");
			break;
		default:
			log("default");
			break;
		}
		//mySprite->setScale((moveTimer/checkTime)+0.5f);

};

//�p�x�̕ۑ�
void PlayerRobot::setAngle(Vec2 from, Vec2 to) 
{
	//cos�Ƃ̒l
	float seta = acos(dot(from,to)/(length(from)*length(to)));
	seta = ragToDeg(seta);
	////log("seta=%f", seta);
	//�E������
	if (cross(from, to) < 0) {
	seta = -seta;
	};
	angles.push_back(seta);
};

//�����n�߂�
void PlayerRobot::moveStartPosition() 
{
	if (myState == STATUS::FIND)return;
	isMove = true;
	nextPosition();
};

//�s���ׂ��Ƃ���̐ݒ�
void PlayerRobot::nextPosition()
{
	SimpleAudioEngine::getInstance()->playEffect("Sounds/move_4.mp3");
	targetPosition = getDirectionDegree(Vec2(1, 0), angles.at(angleNum), doubtDegree) + myPosition;
	angleNum++;
};

//�����~�܂�����
void PlayerRobot::stopPosition()
{
	moveRangeSp->clear();
	angles.clear();
	
	isMove = false;
	targetPosition = myPosition;
	moveRangeSp->drawCircle(Vec2(0, 0), moveRange, 0, 360, false, Color4F::BLACK);
	angleNum = 0;
	startPosition = myPosition;
	setState(STATUS::STOP);
	stopAnimation();
};

//�S�[�����������Ƃ�
void PlayerRobot::findPosition() 
{
	moveRangeSp->clear();
	angles.clear();

	isMove = false;
	angleNum = 0;
	findAnimation();
	setState(STATUS::FIND);
};

//�~�܂������̃A�j���[�V����
void PlayerRobot::stopAnimation() 
{
	messageSp->setVisible(true);

	ScaleTo* scaleIn = ScaleTo::create(0.5f, 2);
	RotateTo* rotateIn = RotateTo::create(0.5f, 15);
	Spawn* spawnIn = Spawn::createWithTwoActions(scaleIn, rotateIn);
	ScaleTo* scaleOut = ScaleTo::create(0.5f, 1);
	RotateTo* rotateOut = RotateTo::create(0.5f, 0);
	Spawn* spawnOut = Spawn::createWithTwoActions(scaleOut, rotateOut);

	messageSp->runAction(Sequence::create(spawnIn, spawnOut, nullptr));
};

void PlayerRobot::findAnimation() 
{
	/*messageSp->setVisible(true);
	messageSp->setTexture("PlayerGoal.png");
*/

	goalPa->setLine(Vec2(-50, 0), Vec2(50, 0));
	goalPa->startParticle();

	/*ScaleTo* scaleIn = ScaleTo::create(0.5f, 2);
	RotateTo* rotateIn = RotateTo::create(0.5f, 15);
	Spawn* spawnIn = Spawn::createWithTwoActions(scaleIn, rotateIn);
	ScaleTo* scaleOut = ScaleTo::create(0.5f, 1);
	RotateTo* rotateOut = RotateTo::create(0.5f, 0);
	Spawn* spawnOut = Spawn::createWithTwoActions(scaleOut, rotateOut);

	messageSp->runAction(Sequence::create(spawnIn, spawnOut, nullptr));*/
};

//�v���C���[�̑��삪�قȂ�̂ŉ��z��
bool PlayerRobot::onTouchBegan(const Touch * touch, Event *unused_event)
{
	if (myState == STATUS::FIND || myState == STATUS::STOP)return false;

			if (onMoveRange(touch->getLocation()))
			{
				isMoveWait = true;
				if (!isStandby)
				{
					endPosition = myPosition + Vec2(1, 0);
				}
			}
			else
			{
				isMoveWait = false;
			}
	return true;
};

void PlayerRobot::onTouchMoved(const Touch * touch, Event *unused_event)
{
	Vec2 touchPosition = touch->getLocation();
	Vec2 stepPosition = myPosition;

	if (myState != STATUS::FIND)
	//��ʊO�ɏo���Ƃ��̏���
		touchPosition = touch->getLocation();
	if (touch->getLocation().x > designResolutionSize.width)
		touchPosition.x = designResolutionSize.width;
	if (touch->getLocation().x < 0)
		touchPosition.x = 0;
	if (touch->getLocation().y > designResolutionSize.height)
		touchPosition.y = designResolutionSize.height;
	if (touch->getLocation().y < 0)
		touchPosition.y = 0;
	//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	//�^�b�`�����Ƃ��ɃL������G���Ă���Ȃ�O���̐ݒ���n�߂�
	if (isMoveWait) {
		//�w�肵�������܂�
		if (angles.size() < MOVE_MAX) 
		{
			//�����œ������ꂽ�Ƃ��ɗ����̂œ��Ԋu�ɂ��邽��while
			while (length(endPosition - touchPosition) >= doubtDegree)
			{
				Vec2 a = Vec2(1, 0);
				Vec2 b = touchPosition - endPosition;
				stepPosition = endPosition;
				endPosition = normalize(touchPosition - endPosition)*doubtDegree + endPosition;
				moveRangeSp->drawDot(endPosition - myPosition, 10, Color4F::BLACK);
				//�O���̕ۑ�
				setAngle(a, b);
			}
		}
	}
	//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
};

void PlayerRobot::onTouchEnded(const Touch * touch, Event *unused_event)
{
	//�����Ă���Ȃ疳���ɂ���
	if (isMove)return;

	angleNum = 0;
	//�����̊m��
	if (angles.size() > 0)
	{
		isStandby = true;
	}
};

