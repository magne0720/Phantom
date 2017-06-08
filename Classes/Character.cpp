#include "Character.h"

Character* Character::create(Vec2 spawnPos, DIR_DEGREE dir)
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

bool Character::init(Vec2 spawnPos, DIR_DEGREE dir)
{
	if (!Node::init()) 
	{
		return false;
	}
	initialize(spawnPos,dir);

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
	plusAction();
};


//初期設定位置
void Character::initialize(Vec2 pos,DIR_DEGREE dir) 
{
	moveRangeSp = DrawNode::create();
	addChild(moveRangeSp,5);
	myPosition = pos;
	targetPosition = pos;
	setPosition(pos);
	setState(STATUS::STAND);
	setDirection(dir);
};


//更新処理
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//マイフレーム起こす移動以外の行動
void Character::action() 
{
	allCollision();

	//	^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// <次ここ！！基本ステート完成させる！！>
	//	YvYvYvYvYvYYvYvYvYvYvYYvYvY

	switch (myState)
	{
	case STAND:
		if (length(targetPosition - myPosition) > moveSpeed) {
			setState(STATUS::MOVE);
		}
		break;
	case MOVE:
		if (length(targetPosition - myPosition) < moveSpeed) {
			setState(STATUS::STAND); 
			break;
		}
		move();
		break;
	case DOUBT:
		break;
	case FIND:
		isMoveWait = true;
		break;
	case CHASE:
		move(2.0f);
		if (length(targetPosition - myPosition) < moveSpeed) { setState(STATUS::STAND); }
		break;
	case DEATH:
		break;
	default:
		break;
	}

//	log("myPosition=[%f,%f]", myPosition.x, myPosition.y);
	//log("targetPosition=[%f,%f]", targetPosition.x, targetPosition.y);
};

//追加行動
void Character::plusAction() 
{


};

//ターゲットに向かって等速で移動する
void Character::move(float plusSpeed) 
{
	//移動に必要
	Vec2 aPos = normalize(targetPosition - myPosition);
	if (getTag() == 0) {
		//log("aPos[%f,%f]", aPos.x, aPos.y);
	}

	moveRangeSp->clear();
	moveRangeSp->drawSegment(Vec2(0,0),targetPosition-myPosition,5,Color4F::GREEN);

	myPosition += aPos*moveSpeed;

	setPosition(myPosition);
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//判定処理
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//今lastTargetPositionにいるか
bool Character::onLastTargetPosition(Vec2 pos) 
{
	if (onCollision(pos, 0.005f)) 
	{
		return true;
	}
	return false;
};


//進む方向が壁かどうか
bool Character::onWall(SEGMENT s0, SEGMENT s1)
{
	//X軸方向のベクトルが0かどうか
	if (s0.to.x == 0.0f || s1.to.x == 0.0f) {
		if (s0.to.x == 0.0f&&s1.to.x == 0.0f)
			return false;
		//平行

		Vec2 r;
		float t0, t1;
		if (s0.to.x == 0.0f) {
			r.x = s0.from.x;
			r.y = (s1.to.y / s1.to.x)*(r.x - s1.from.x) + s1.from.y;

			t0 = (r.y - s0.from.y) / s0.to.y;		//t=0~1の時は線分s0内
			t1 = (r.x - s1.from.x) / s1.to.x;		//t=0~1の時は線分s1内
		}
		else {
			r.x = s1.from.x;
			r.y = (s0.to.y / s0.to.x)*(r.x - s0.from.x) + s0.from.y;

			t0 = (r.x - s0.from.x) / s0.to.x;		//t=0~1の時は線分s0内
			t1 = (r.y - s1.from.y) / s1.to.y;		//t=0~1の時は線分s1内
		}
		if ((t0<0.0f) || (t0>1.0f) || (t1 < 0.0f) || (t1 > 1.0f))return false;
		return true;
	}
	else {
		//線分の傾きを求める
		float a0 = s0.to.y / s0.to.x;
		float a1 = s1.to.y / s1.to.x;

		//傾きが同一の場合は平行なので衝突しない
		if ((a0 == a1) || a0 == -a1)return false;

		//交点のx,y座標を求める
		Vec2 r;
		r.x = (a0*s0.from.x - a1*s1.from.x + s1.from.y - s0.from.y) / (a0 - a1);
		r.y = a0*(r.x - s0.from.x) + s0.from.y;

		//交点が線分内にあるか調べる
		float t0 = (r.x - s0.from.x) / s0.to.x;		//t=0~1の時は線分s0内
		float t1 = (r.x - s1.from.x) / s1.to.x;		//t=0~1の時は線分s1内

		if ((t0<0.0f) || (t0>1.0f) || (t1<0.0f) || (t1>1.0f))return false;

		return true;
	}

	return false;
};

//タッチした位置が移動範囲かどうか
bool Character::onMoveRange(Point target)
{
	if ((target.x - myPosition.x)*(target.x - myPosition.x)
		+ (target.y - myPosition.y)*(target.y - myPosition.y) <= moveRange*moveRange)
	{
		return true;
	}
	return false;
};

//右側から見て内側にあるか
bool Character::onDirectionRight(const Vec2 target)
{
	//自身の向いている方向から右に視認範囲分回転
	Vec2 to = getDirectionDegree(getDirectionVector(), -doubtDegree,moveRange);
	//敵の位置
	Vec2 t = target-myPosition;

	if (to.x*t.y - t.x*to.y < 0)
	{
		return true;
	}
	return false;
};

//左側から見て内側にあるか
bool Character::onDirectionLeft(const Vec2 target)
{
	//自身の向いている方向から右に視認範囲分回転
	Vec2 to = getDirectionDegree(getDirectionVector(), doubtDegree, moveRange);
	//敵の位置
	Vec2 t = target - myPosition;

	if (to.x*t.y - t.x*to.y > 0)
	{
		return true;
	}
	return false;
};

//衝突判定まとめ
void Character::allCollision()
{
	SEGMENT mySeg = SEGMENT(myPosition, targetPosition);
	Vec2 movement = targetPosition - myPosition;

	for (int i = 0; i < walls.size(); i++)
		for (int j = 0; j < walls.at(i)->segmentCount; j++)
		{
			if (onWall(mySeg,SEGMENT(walls.at(i)->points[j],walls.at(i)->getOverPoint(walls.at(i)->points,walls.at(i)->segmentCount,j+1))))
			{
				setEvasionWall(walls.at(i)->getSegment(j), movement);
			}
		}
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//セッター
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//状態変化
void Character::setState(STATUS state)
{
	myState = state;
};

//速度変更
void Character::setSpeed(float speed) 
{
	moveSpeed = speed;
};

void Character::setTargetWall(Wall* p)
{
	walls.pushBack(p);
};


//歩ける範囲変更
void Character::setMoveRange(float range)
{
	moveRange = range;
};

//視認範囲設定
void Character::setDoubtDgree(float range) 
{
	doubtDegree = range;
};

//移動場所設定
void Character::setTargetPosition(Vec2 pos) 
{
	targetPosition = pos;
}

//360度の向き変更
void Character::setDirection(float degree)
{
	myDirection = degree;
};

//固定値に向き変更
void Character::setDirection(DIR_DEGREE degree)
{
	switch (degree)
	{
	case DIR_RIGHT:
		targetPosition.x += 1.0f;
		break;
	case DIR_UP:
		targetPosition.y += 1.0f;
		break;
	case DIR_LEFT:
		targetPosition.x -= 1.0f;
		break;
	case DIR_DOWN:
		targetPosition.y -= 1.0f;
		break;
	default:
		break;
	}
	myDirection = (float)degree;
};


//方向ベクトルから右方向に固有角度で自身の視認範囲のベクトルを取得する
Vec2 Character::getDirectionDegree(Vec2 target, float deg, float range)
{
	Vec2 vector = normalize(target);
	//ラジアンに変換
	float rag=degToRag(deg);

	float ax = vector.x*cos(rag) - vector.y*sin(rag);
	float ay = vector.x*sin(rag) + vector.y*cos(rag);

	vector.x = ax*range;
	vector.y = ay*range;

	return vector;
};

//向きによってもらうベクトルと進む方向でどちらの方向に回転するかを決める(壁ずり)
void Character::setEvasionWall(Vec2 wall, Vec2 target)
{
	// out : 正規化壁ずりベクトル（戻り値）
	// front : 進行ベクトル
	// normal: 衝突点での法線ベクトル
	//(front - Dot(&front, &normal_n) * normal_n)


	Vec2 t ;
	//壁の法線
	Vec2 wall_n = getDirectionDegree(wall, 90);

	log("%d,wall_n=[%0.2f,%0.2f]",getTag(), wall_n.x, wall_n.y);

	targetPosition = target - dot(target, wall_n)*wall_n+myPosition;

	//if (length(t-myPosition) > moveSpeed) 
	//{
	//	log("top");
	//	targetPosition = t;
	//}
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//ゲッター
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//自身の向いている方向を指しているvectorを返す
Vec2 Character::getDirectionVector()
{
	if(myDirection>0&&myDirection<45||myDirection>315&&myDirection<=360)
	{

	}
	return normalize(myPosition-targetPosition);
};


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




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
