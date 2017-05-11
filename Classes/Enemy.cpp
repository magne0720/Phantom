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

//プレイヤーがいるかどうか確認
bool Enemy::checkPlayer(Vec2 playerPos)
{
	float len = length(playerPos-myPosition);

	//その距離が判定内なら
	if (len <= doubtRange)
	{
		//扇形の判定をする
		if (onDirectionRight(playerPos)&&onDirectionLeft(playerPos))
		{
			setTargetPosition(playerPos);
			//追う状態へ。
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

//視認範囲変更
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

//衝突判定まとめ
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



