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
	myPosition = spawnPos;
	targetPosition = spawnPos;
	setSpeed(3.0f);
	moveRange = 500.0f;
	doubtRange = moveRange;
	doubtDegree = 45;
	initWithFileCenter("Enemy.png");
	setColor(Color3B::BLACK);
	myDirection = dir;
	setPosition(spawnPos);

	moveRangeSp = DrawNode::create();
	changeDegree(doubtDegree);
	addChild(moveRangeSp);


	scheduleUpdate();

	return true;
};

void Enemy::update(float delta) 
{
	action();
};
//���������
void Enemy::action() 
{
	switch (myState)
	{
	case STAND:
		break;
	case MOVE:
		move();
		break;
	case DOUBT:
		break;
	case FIND:
		break;
	case CHASE:
		move();
		break;
	case DEATH:
		break;
	default:
		break;
	}
};

//�v���C���[�����邩�ǂ����m�F
bool Enemy::checkPlayer(Vec2 playerPos)
{
	//���g�ƃv���C���[�̋��������߂�
	float x = playerPos.x - myPosition.x;
	float y = playerPos.y - myPosition.y;

	float length = sqrt(x*x + y*y);

	//���̋�����������Ȃ�
	if (length <= doubtRange)
	{
		//��`�̔��������
		if (getDirectionLeft(playerPos - myPosition) && getDirectionRight(playerPos - myPosition)) 
		{
			targetPosition = playerPos;
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

void Enemy::changeDegree(float degree) 
{
	doubtDegree = degree;
	moveRangeSp->clear();
	for (int deg = 0; deg < degree; deg++)
	{
		moveRangeSp->drawSegment(getPosition() - myPosition, getDirectionDegree(deg, moveRange), 3, Color4F::WHITE);
		moveRangeSp->drawSegment(getPosition() - myPosition, getDirectionDegree(-deg, moveRange), 3, Color4F::WHITE);
	}
};

//��ԕω�
void Enemy::setState(STATUS state)
{
	myState = state;
};

