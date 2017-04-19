#include "Enemy.h"

Enemy* Enemy::create(Vec2 spawnPos) 
{
	Enemy *pRet = new Enemy();
	if (pRet && pRet->init(spawnPos))
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

bool Enemy::init(Vec2 spawnPos) 
{

	myPosition = spawnPos;
	targetPosition = spawnPos;
	moveSpeed = 3.0f;
	moveRange = 300.0f;
	doubtRange = moveRange;
	initWithFileCenter("Enemy.png");
	setColor(Color3B::BLACK);

	moveRangeSp = DrawNode::create();
	moveRangeSp->drawCircle(getPosition(), doubtRange, 0, 360, false, Color4F::YELLOW);
	addChild(moveRangeSp);

	setPosition(spawnPos);

	scheduleUpdate();

	return true;


};


void Enemy::action() 
{

};



//プレイヤーがいるかどうか確認
bool Enemy::checkPlayer(Vec2 playerPos) 
{
	//自身とプレイヤーの距離を求める
	float x = playerPos.x - myPosition.x;
	float y = playerPos.y - myPosition.y;

	float length = sqrt(x*x + y*y);

	//その距離が判定内なら
	if (length <= doubtRange)
	{

		//扇形の判定をする
		targetPosition = playerPos;

		return true;
	}




	return true;
};

bool Enemy::checkPlayerRight(float Range) 
{
	return false;
};

bool Enemy::checkPlayerLeft(float Range) 
{
	return false;
};

//状態変化
void Enemy::setState(STATUS state)
{
	myState = state;
};

