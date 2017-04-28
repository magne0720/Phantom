#include "Character.h"

Character* Character::create(Vec2 spawnPos)
{
	Character *pRet = new Character();
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

bool Character::init(Vec2 spawnPos)
{
	if (!Node::init()) 
	{
		return false;
	}
	myPosition =spawnPos;
	targetPosition = spawnPos;
	moveSpeed = 12.0f;

	initWithFileCenter("CloseNormal.png");
	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	// 対象のイベントが実行された後、下位のイベントは発動されなくする
	listener->onTouchBegan = CC_CALLBACK_2(Character::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Character::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Character::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();

	return true;
};

void Character::update(float delta) 
{
	action();
	move();
};

//画像を中央にして自身の画像を置く
void Character::initWithFileCenter(std::string name) 
{
	mySprite = Sprite::create(name);
	mySprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	addChild(mySprite,5);
};

//タッチした位置が移動範囲かどうか
bool Character::canMoveRange(Point target)
{
	if ((target.x- myPosition.x)*(target.x - myPosition.x)
		+ (target.y-myPosition.y)*(target.y- myPosition.y) <= moveRange*moveRange)
	{
		return true;
	}
	return false;
};

//マイフレーム起こす移動以外の行動
void Character::action() 
{

};

//ターゲットに向かって等速で移動する
void Character::move() 
{

	//移動に必要
	Vec2 aPos = normalize(targetPosition-myPosition);
	Vec2 bPos = Vec2(1, 0);

	//向きを調べるのに必要

	//向き(右方向が０度)
	float s = (aPos.x*bPos.y+bPos.x*aPos.y)/(length(aPos)*length(bPos));
	float seta = acos(s)*180.0f / M_PI;
	if (seta < 0)
		seta = seta*(-1);

	//moveRangeSp->setRotation(-seta / doubtDegree);
	setDirection(seta,doubtDegree);
	
	if (abs(myPosition.x-targetPosition.x) <= moveSpeed && abs(myPosition.y- targetPosition.y) <= moveSpeed ) { return; }
	
	myPosition += aPos*moveSpeed;

	setPosition(myPosition);
};

//衝突判定
bool Character::onCollision(float deg) 
{
	return false;
};

//線に当たっているかどうか
bool Character::onCollision(Vec2 start, Vec2 end)
{
	Vec2 AB = end - start;
	Vec2 AP = myPosition - start;
	Vec2 BP = myPosition - end;

	//外積
	float APxAB = AB.x*AP.y - AP.x*AB.y;
	if (APxAB < 0)APxAB = APxAB*(-1);

	//内積
	float DotAP = dot(AP, AB);
	float DotBP = dot(BP, AB);

	float ans = APxAB / sqrt(AB.x*AB.x + AB.y*AB.y);
	
	if (ans <= 100.0f)
	{
		if (DotAP*DotBP <= 0)
		{
			mySprite->setColor(Color3B::RED);
			moveRangeSp->setVisible(true);
			return true;
		}
		else
		{
			if (ans > sqrt(AP.x*AP.x + AP.y*AP.y)||ans>sqrt(BP.x*BP.x+BP.y*BP.y)) 
			{
				mySprite->setColor(Color3B::RED);
				moveRangeSp->setVisible(true);
				return true;
			}
			mySprite->setColor(Color3B::WHITE);
			moveRangeSp->setVisible(false);
			return false;
		}
	}
	else 
	{
		mySprite->setColor(Color3B::WHITE);
		moveRangeSp->setVisible(false);
		return false;
	}
	return false;
};

void Character::setSpeed(float speed) 
{
	moveSpeed = speed;
};

void Character::setMoveRange(float range)
{
	moveRange = range;
};

//X(４５度刻みで方向確認)
void Character::setDirection(float seta,float alpha)
{
	if (seta > 0) {
		if (seta <= 45)
			myDirection = DIR_DEGREE::DIR_RIGHT;
		else if (seta <= 135)
			myDirection = DIR_DEGREE::DIR_UP;
		else
			myDirection = DIR_DEGREE::DIR_LEFT;
	}
	else if (seta < 0) {
		if (seta >= -45)
			myDirection = DIR_DEGREE::DIR_RIGHT;
		else if (seta >= -135)
			myDirection = DIR_DEGREE::DIR_DOWN;
		else
			myDirection = DIR_DEGREE::DIR_LEFT;
	}
};

//当たり判定のあるものを設定
//すでにあるなら追加しない
void Character::setTarget(Character* p)
{
	targets.pushBack(p);
};

//当たり判定のあるものを設定
//すでにあるなら追加しない
void Character::setTarget(Wall* p)
{
	walls.pushBack(p);
};


//方向取得(ターゲットの方向を前方向とする)
Vec2 Character::getDirectionVector(Vec2 target,float range)
{
	Vec2 vector = target;

	switch (myDirection)
	{
	case DIR_DEGREE::DIR_RIGHT:
		vector.x += 1.0f;
		break;
	case DIR_DEGREE::DIR_UP:
		vector.y += 1.0f;
		break;
	case DIR_DEGREE::DIR_LEFT:
		vector.x -= 1.0f;
		break;
	case DIR_DEGREE::DIR_DOWN:
		vector.y -= 1.0f;
		break;
	default:
		break;
	}
	normalize(vector);

	return vector;
};

//方向ベクトルから右方向に固有角度で自身の視認範囲のベクトルを取得する
Vec2 Character::getDirectionDegree(Vec2 target,float deg,float range)
{
	Vec2 vector = getDirectionVector(target);

	//ラジアンに変換
	deg *= M_PI / 180;

	float ax = vector.x*cos(deg) - vector.y*sin(deg);
	float ay = vector.x*sin(deg) + vector.y*cos(deg);

	vector.x = ax*range;
	vector.y = ay*range;

	return vector;
};

//右側から見て内側にあるか
bool Character::getDirectionRight(Vec2 target) 
{
	Vec2 r = getDirectionDegree(targetPosition-myPosition,-doubtDegree,moveRange);

	if(r.x*target.y-target.x*r.y > 0)
	{
		return true;
	}
	return false;
};

//左側から見て内側にあるか
bool Character::getDirectionLeft(Vec2 target)
{
	Vec2 l = getDirectionDegree(targetPosition-myPosition,doubtDegree, moveRange);

	if (l.x*target.y - target.x*l.y < 0)
	{
		return true;
	}
	return false;
};

//進む方向が壁かどうか
bool Character::checkWall(Vector<Wall*> quad)
{
	Vec2 forward = targetPosition-myPosition;
	Vec2 xy1, xy2, xy3, xy4,ans;
	float len = 5000.0f;
	forward.normalize();
	forward = forward*50.0f + myPosition;

	for (int i = 0; i < quad.size(); i++) {

		xy1 = quad.at(i)->points[0] - quad.at(i)->points[1] + quad.at(i)->getPosition();
		xy2 = quad.at(i)->points[1] - quad.at(i)->points[2] + quad.at(i)->getPosition();
		xy3 = quad.at(i)->points[2] - quad.at(i)->points[3] + quad.at(i)->getPosition();
		xy4 = quad.at(i)->points[3] - quad.at(i)->points[4] + quad.at(i)->getPosition();

		//if ((xy2.x - xy1.x)*(forward.y - xy1.y) - (forward.x - xy1.x)*(xy2.y - xy1.y) < 0)
		//	if ((xy3.x - xy2.x)*(forward.y - xy2.y) - (forward.x - xy2.x)*(xy3.y - xy2.y) < 0)
		//		if ((xy4.x - xy3.x)*(forward.y - xy3.y) - (forward.x - xy3.x)*(xy4.y - xy3.y) < 0)
		//			if ((xy1.x - xy4.x)*(forward.y - xy4.y) - (forward.x - xy4.x)*(xy1.y - xy4.y) < 0)
		//			{
		//				for (int j = 0; j < 4; j++)
		//				{
		//					if (length(quad.at(i)->points[j+1]-myPosition) < len)
		//					{
		//						len = length(quad.at(i)->points[j+1] - myPosition);
		//						log("ans[%d]", j);
		//						ans = quad.at(i)->points[j+1]-quad.at(i)->points[j];
		//						myDirection = (DIR_DEGREE)((j+1)*90);
		//					}
		//				}
		//				checkEvasionWall(ans, targetPosition-myPosition);
		//				//setState(STATUS::STAND);
		//				return true;
		//			}

		if (onCollision(xy1, xy2))//左側
		{
			checkEvasionWall(xy1 - xy2, forward);
			return true;
		}
		if (onCollision(xy2, xy3))//上側
		{
			checkEvasionWall(xy2 - xy3, forward);
			return true;
		}
		if (onCollision(xy3, xy4))//右側
		{
			checkEvasionWall(xy3 - xy4, forward);
			return true;
		}
		if (onCollision(xy4, xy1))//下側
		{
			checkEvasionWall(xy4 - xy1, forward);
			return true;
		}
	}
	return false;
};

//向きによってもらうベクトルと進む方向でどちらの方向に回転するかを決める(壁ずり)
void Character::checkEvasionWall(Vec2 wall, Vec2 target) 
{
	//法線
	Vec2 n = getDirectionDegree(wall,90);
	normalize(n);
	float a = dot(-target, n);

	targetPosition = target + a * n;
	//log("%f%f", targetPosition.x, targetPosition.y);
};


//状態変化
void Character::setState(STATUS state)
{
	myState = state;
};

//正規化
Vec2 Character::normalize(Vec2 &pos) 
{
	float mag = 1 / sqrt(pos.x*pos.x + pos.y*pos.y);
	pos.x *= mag;
	pos.y *= mag;

	return pos;
};

float Character::length(Vec2 pos) 
{
	return sqrt(pos.x*pos.x + pos.y*pos.y);
};

//内積
float Character::dot(Vec2 from, Vec2 to) 
{
	return from.x*to.x + from.y*to.y;
};


bool Character::onTouchBegan(const Touch * touch, Event *unused_event) 
{
	return true;
};

void Character::onTouchMoved(const Touch * touch, Event *unused_event)
{

};

void Character::onTouchEnded(const Touch * touch, Event *unused_event)
{

};
