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

	setState(STATUS::MOVE);

	scheduleUpdate();

	return true;
};

void Enemy::update(float delta) 
{
	checkPlayer(targets.at(PLAYER_AI)->myPosition);
	checkPlayer(targets.at(PLAYER_HANSOME)->myPosition);
	onCollision(targets.at(PLAYER_AI)->myPosition, targets.at(PLAYER_HANSOME)->myPosition);
	checkWall(walls);
	action();
};
//次ここやる
void Enemy::action() 
{
	switch (myState)
	{
	case STAND:
		moveThink(1.0f);
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

//プレイヤーがいるかどうか確認
bool Enemy::checkPlayer(Vec2 playerPos)
{
	//自身とプレイヤーの距離を求める
	Vec2 pos = playerPos - myPosition;

	float len = length(pos);

	//その距離が判定内なら
	if (len <= doubtRange)
	{
		//扇形の判定をする
		if (getDirectionLeft(playerPos - myPosition) && getDirectionRight(playerPos - myPosition))
		{
			targetPosition = playerPos;
			//追う状態へ。
			changeDegree(75);
			if (myState != STATUS::STAND)
			{
				setState(STATUS::CHASE);
			}
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
		moveRangeSp->drawSegment(getPosition() - myPosition, changeDirectionDegree(targetPosition-myPosition,deg, moveRange), 5, Color4F::MAGENTA);
		moveRangeSp->drawSegment(getPosition() - myPosition, changeDirectionDegree(targetPosition-myPosition,-deg, moveRange), 5, Color4F::MAGENTA);
	}
};

//移動するか試行する
void Enemy::moveThink(float time) 
{
	thinkTimer -= time;
	if (thinkTimer < 0) 
	{
		setState(STATUS::MOVE);
		//いったん20フレーム設定
		thinkTimer = 20;
	}
}
