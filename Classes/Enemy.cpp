#include "Enemy.h"

Enemy* Enemy::create(Vec2 spawnPos,DIR_DEGREE dir) 
{
	Enemy *pRet = new Enemy();
	if (pRet && pRet->init(spawnPos,dir))
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

bool Enemy::init(Vec2 spawnPos,DIR_DEGREE dir) 
{
	setSpeed(3.0f);
	moveRange = 500.0f;
	doubtRange = moveRange;
	doubtDegree = 30;
	initWithFileCenter("Enemy.png");
	setColor(Color3B::BLACK);
	myDirection = dir;

	initialize(spawnPos);
	targetPosition.x += 1.0f;
	

	moveRangeSp = DrawNode::create();
	changeDegree(doubtDegree);
	addChild(moveRangeSp);

	setState(STATUS::STAND);

	scheduleUpdate();

	return true;
};

void Enemy::plusAction() 
{
	switch (myState)
	{
	case STAND:
		allCollision();
		break;
	case MOVE:
		allCollision();
		onWall(walls);
		move();
		break;
	case DOUBT:
		allCollision();
		break;
	case FIND:
		allCollision();
		break;
	case CHASE:
		allCollision();
		break;
	case DEATH:
		moveRangeSp->clear();
		moveRangeSp->drawCircle(Vec2(0, 0), moveRange, 0, 360, false, Color4F::RED);
		break;
	default:
		break;
	}




};

//�v���C���[�����邩�ǂ����m�F
bool Enemy::checkPlayer(Vec2 playerPos)
{
	float len = length(playerPos-myPosition);

	//���̋�����������Ȃ�
	if (len <= doubtRange)
	{
		//��`�̔��������
		if (onDirectionRight(playerPos)&&onDirectionLeft(playerPos))
		{
			setTargetPosition(playerPos);
			//�ǂ���ԂցB
			changeDegree(75);
			setState(STATUS::CHASE);
		}
		return true;
	}
	return false;
};

void Enemy::changeRange(float range) 
{
	moveRange = range;
};

//���F�͈͕ύX
void Enemy::changeDegree(float degree) 
{
	doubtDegree = degree;
	moveRangeSp->clear();
	for (int deg = 0; deg < degree; deg++)
	{
		moveRangeSp->drawSegment(Vec2(0, 0), getDirectionDegree(targetPosition - myPosition, -deg, moveRange), 5, Color4F::MAGENTA);
		moveRangeSp->drawSegment(Vec2(0, 0), getDirectionDegree(targetPosition - myPosition,  deg, moveRange), 5, Color4F::MAGENTA);
	}
};

//�ړ����邩���s����
void Enemy::moveThink(float time) 
{
	thinkTimer -= time;
	if (thinkTimer < 0) 
	{
		setState(STATUS::MOVE);
		//��������20�t���[���ݒ�
		thinkTimer = 20;
	}
}

//�Փ˔���܂Ƃ�
void Enemy::allCollision() 
{
	if (myState != STATUS::DEATH)
	{
		checkPlayer(targets.at(PLAYER_AI)->myPosition);
		checkPlayer(targets.at(PLAYER_HANSOME)->myPosition);
	}
	if (onCollision(targets.at(PLAYER_AI)->myPosition, targets.at(PLAYER_HANSOME)->myPosition))
	{
		setState(STATUS::DEATH);
	}
};



