#include "Wall.h"

Wall* Wall::create(Vec2 spawnPos) 
{
	Wall *pRet = new Wall();
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

bool Wall::init(Vec2 spawnPos) 
{
	if (!Node::init()) 
	{
		return false;
	}
	setPosition(spawnPos);
	myPosition = spawnPos;

	mySprite = Sprite::create("Sphere.png");
	addChild(mySprite);


	//segments[0] = Vec2(mySprite->getBoundingBox().getMinX() + spawnPos.x, mySprite->getBoundingBox().getMinY() + spawnPos.y);//左下
	//segments[1] = Vec2(mySprite->getBoundingBox().getMinX() + spawnPos.x, mySprite->getBoundingBox().getMaxY() + spawnPos.y);//左上
	//segments[2] = Vec2(mySprite->getBoundingBox().getMaxX() + spawnPos.x, mySprite->getBoundingBox().getMaxY() + spawnPos.y);//右上
	//segments[3] = Vec2(mySprite->getBoundingBox().getMaxX() + spawnPos.x, mySprite->getBoundingBox().getMinY() + spawnPos.y);//右下
	//segments[4] = Vec2(mySprite->getBoundingBox().getMinX() + spawnPos.x, mySprite->getBoundingBox().getMinY() + spawnPos.y);//左下(for文でif処理をなくすため)

	Rect r = mySprite->getBoundingBox();

	segments[0] = SEGMENT(Vec2(r.getMinX() + spawnPos.x, r.getMinY() + spawnPos.y), Vec2(r.getMinX()+spawnPos.x, r.getMaxY() + spawnPos.y));//左
	segments[1] = SEGMENT(Vec2(r.getMinX() + spawnPos.x, r.getMaxY() + spawnPos.y), Vec2(r.getMaxX()+spawnPos.x, r.getMaxY() + spawnPos.y));//上
	segments[2] = SEGMENT(Vec2(r.getMaxX() + spawnPos.x, r.getMaxY() + spawnPos.y), Vec2(r.getMaxX()+spawnPos.x, r.getMinY() + spawnPos.y));//右
	segments[3] = SEGMENT(Vec2(r.getMaxX() + spawnPos.x, r.getMinY() + spawnPos.y), Vec2(r.getMinX()+spawnPos.x, r.getMinY() + spawnPos.y));//下
	segments[4] = SEGMENT(Vec2(0,0),Vec2(0,0));//5角形になった時用

	DrawNode* a = DrawNode::create();
	//a->setPosition(a->getPosition() - spawnPos);
	a->drawSegment(segments[0].s, segments[0].s + segments[0].v, 5, Color4F::GRAY);
	a->drawSegment(segments[1].s, segments[1].s + segments[1].v, 5, Color4F::GRAY);
	a->drawSegment(segments[2].s, segments[2].s + segments[2].v, 5, Color4F::GRAY);
	a->drawSegment(segments[3].s, segments[3].s + segments[3].v, 5, Color4F::GRAY);
	a->drawSegment(segments[4].s, segments[4].s + segments[4].v, 5, Color4F::GRAY);
	addChild(a);

	//log("myPosition\n[%f,%f]", getPosition().x, getPosition().y);
	//for (int i = 0;i < 4; i++) {
	//	log("%d[%f,%f]", i,segments[i].x+getPositionX(), segments[i].y+getPositionY());
	//}


	return true;
};

//新しくポイントを設定する
void Wall::setPoint(int number, Vec2 point) 
{
//	segments[number] = point;
};

//from-to間の線とtargetの交点を調べる
int Wall::checkPoint(Vec2* hitPos,SEGMENT s0,SEGMENT s1)
{
	//X軸方向のベクトルが0かどうか
	if (s0.v.x == 0.0f || s0.v.y == 0.0f) {
		if (s0.v.x == 0.0f&&s0.v.y == 0.0f)
			return 0;//平行

		Vec2 r;
		float t0, t1;
		if (s0.v.x == 0.0f) {
			r.x = s0.s.x ;
			r.y = (s1.v.y / s1.v.x)*(r.x - s1.s.x) + s1.s.y;

			t0 = (r.y - s0.s.y) / s0.v.y;		//t=0~1の時は線分s0内
			t1 = (r.x - s1.s.x) / s1.v.x;		//t=0~1の時は線分s1内
		}
		else {
			r.x = s1.s.x;
			r.y = (s0.v.y / s0.v.x)*(r.x - s0.s.x) + s0.s.y;

			t0 = (r.x - s0.s.x) / s0.v.x;		//t=0~1の時は線分s0内
			t1 = (r.y - s1.s.y) / s1.v.y;		//t=0~1の時は線分s1内
		}
		if ((t0<0.0f) || (t0>1.0f) || (t1 < 0.0f) || (t1 > 1.0f))return 0;
		if (hitPos) *hitPos = r;
		return 1;
	}
	else {
		//線分の傾きを求める
		float a0 = s0.v.y / s0.v.x;
		float a1 = s1.v.y / s1.v.x;

		//傾きが同一の場合は平行なので衝突しない
		if ((a0 == a1) || a0 == -a1)return 0;

		//交点のx,y座標を求める
		Vec2 r;
		r.x = (a0*s0.s.x - a1*s1.s.x + s1.s.y - s0.s.y) / (a0 - a1);
		r.y = a0*(r.x - s0.s.x) + s0.s.y;

		//交点が線分内にあるか調べる
		float t0 = (r.x - s0.s.x) / s0.v.x;		//t=0~1の時は線分s0内
		float t1 = (r.x - s1.s.x) / s1.v.x;		//t=0~1の時は線分s1内

		if ((t0<0.0f) || (t0>1.0f) || (t1<0.0f) || (t1>1.0f))return 0;

		//衝突していることを返す
		if (hitPos)*hitPos = r;
		return 1;
	}
		//log("[%d]=%f,%f", num,px,py);
};

//切り取られる演出
void Wall::cutEffect()
{

};

//start-end間に当たっているかどうか
bool Wall::onCollision(Vec2 start, Vec2 end)
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
			return true;
		}
		else
		{
			if (ans > sqrt(AP.x*AP.x + AP.y*AP.y) || ans>sqrt(BP.x*BP.x + BP.y*BP.y))
			{
				return true;
			}
			return false;
		}
	}
	else
	{
		return false;
	}
	return false;
};
