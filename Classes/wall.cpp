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
	//addChild(mySprite);

	Rect r = mySprite->getBoundingBox();

	segments[0] = SEGMENT(Vec2(r.getMinX() + spawnPos.x, r.getMinY() + spawnPos.y), Vec2(r.getMinX()+spawnPos.x, r.getMaxY() + spawnPos.y));//左
	segments[1] = SEGMENT(Vec2(r.getMinX() + spawnPos.x, r.getMaxY() + spawnPos.y), Vec2(r.getMaxX()+spawnPos.x, r.getMaxY() + spawnPos.y));//上
	segments[2] = SEGMENT(Vec2(r.getMaxX() + spawnPos.x, r.getMaxY() + spawnPos.y), Vec2(r.getMaxX()+spawnPos.x, r.getMinY() + spawnPos.y));//右
	segments[3] = SEGMENT(Vec2(r.getMaxX() + spawnPos.x, r.getMinY() + spawnPos.y), Vec2(r.getMinX()+spawnPos.x, r.getMinY() + spawnPos.y));//下
	segments[4] = SEGMENT(Vec2(0, 0), Vec2(0, 0));//5角形になった時用
	segments[5] = SEGMENT(Vec2(0, 0), Vec2(0, 0));//分割時に必要になる


	myWall = DrawNode::create();
	myWall->setPosition(myWall->getPosition() - spawnPos);

	//頂点座標設定
	std::vector<Vec2>vecs;
	vecs.push_back(segments[0].s);
	vecs.push_back(segments[1].s);
	vecs.push_back(segments[2].s);
	vecs.push_back(segments[3].s);

	myWall->drawPolygon(&vecs[0], 4, Color4F::WHITE, 1, Color4F::YELLOW);
	myWall->setPosition(-spawnPos);
	this->addChild(myWall);

	clipp = ClippingNode::create();
	clipp->setStencil(myWall);
	clipp->addChild(mySprite);
	addChild(clipp);

	isCuted = false;

	scheduleUpdate();

	return true;
};

void Wall::update(float delta) 
{
	/*if (isCuted) 
	{
		cutTimer += delta;
		if (cutTimer >= 5.0f) isCuted = false;
	}*/
}

void Wall::setTargets(Vec2* from, Vec2* to) 
{
	fromPos = from;
	toPos = to;
};

//新しくポイントを設定する
void Wall::setPoint(int number, Vec2 point) 
{
//	segments[number] = point;
};

//衝突判定命令
void Wall::callCollision() 
{
	if (isCuted)return;
	isCuted = true;
	Vec2 pos;
	int count = 4;
	for (int i = 0; i < count; i++) {
		if (checkPoint(&pos, SEGMENT(*fromPos, *toPos), segments[i]) == 1)
		{
			cutSegment(&pos, segments[i], segments[count]);
			i++;
			sortSegment(count, i, count - 4);
			count++;
		}
	}
		if (count == 6)
		{
			checkCutArea();
		}
};

//from-to間の線とtargetの交点を調べる
int Wall::checkPoint(Vec2* hitPos, SEGMENT s0, SEGMENT s1)
{
	//X軸方向のベクトルが0かどうか
	if (s0.v.x == 0.0f || s1.v.x == 0.0f) {
		if (s0.v.x == 0.0f&&s1.v.x == 0.0f)
			return 0;
		//平行

		Vec2 r;
		float t0, t1;
		if (s0.v.x == 0.0f) {
			r.x = s0.s.x;
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
};

//検出した点が含まれている線を検出した点を境に分割する
void Wall::cutSegment(Vec2* hitPos, SEGMENT& from, SEGMENT& out) 
{
	SEGMENT seg;

	seg.v = from.v-*hitPos+from.s;
	seg.s = *hitPos;

	from.v = seg.s;
	out = seg;
};

//配列の中を先頭から3つずつ取り出した点で面積の合計を返す
float Wall::sumArea(int point[]) 
{
	float area = 0;
	for (int i = 0; point[i+2] != -1; i++) 
	{
		area += (length(segments[point[i]].s - segments[point[i+1]].s)+ length(segments[point[i+1]].s - segments[point[i+2]].s)+ length(segments[point[i+2]].s - segments[point[i]].s))/2;
	}
	return area;
};

//角の頂点をなくして、その頂点をつないでいた線同士をつないだ5角形を作る
void Wall::changePentagon(int pointNum) 
{
	SEGMENT s[6];
	//頂点がなくなるので、その前の点とそのあとの点をつなぐ
	segments[pointNum - 1].v = segments[pointNum + 1].s;
	//いらない頂点を消す
	for (int i = pointNum; i < 5; i++) 
	{
		segments[i] = segments[i + 1];
	}
	////6番目は使わないので初期化
	//segments[5] = SEGMENT(Vec2(0, 0), Vec2(0, 0));
};

//切り取る場所検出
void Wall::checkCutArea()
{
	SEGMENT sSeg[6];
	int right[6], left[6];
	int rightcount = 0, leftcount = 0;
	for (int i = 0; i < 6; i++) {
		if (i != addPointNum[0] && i != addPointNum[1])
			//追加した二つの点でできた線の右側かどうか
			if (cross(segments[addPointNum[0]].s - segments[addPointNum[1]].s, segments[addPointNum[0]].s - segments[i].s)>0)
			{
				right[rightcount] = i;
				rightcount++;
			}
			else {
				left[leftcount] = i;
				leftcount++;
			}
	}
		//結果が四角形になる場合
		if (rightcount == 2 && leftcount == 2)
		{
			//分割線を追加
			right[rightcount++] = addPointNum[0];
			right[rightcount++] = addPointNum[1];
			right[rightcount] = -1;//NULLコード

			left[leftcount++] = addPointNum[0];
			left[leftcount++] = addPointNum[1];
			left[leftcount] = -1;//NULLコード


			//面積比を見る
			if (sumArea(right) > sumArea(left))
			{
				//左側が消える
				for (int j = 0; right[j]!=-1; j++) 
				{
					sSeg[j] = segments[right[j]];
				}
			}
			else 
			{
				//右側が消える
				for (int j = 0; left[j] != -1; j++)
				{
					sSeg[j] = segments[left[j]];
				}
			}

			//segments[4] = SEGMENT(Vec2(0, 0), Vec2(0, 0));//いらなくなった場所
			//segments[5] = SEGMENT(Vec2(0, 0), Vec2(0, 0));//いらなくなった場所


			for (int w = 0; w < 6; w++) 
			{
				segments[w] = sSeg[w];
			//	log("[%d]=[%f,%f]", w, segments[w].s.x, segments[w].s.y);
			}

			if (addPointNum[0] ==1)//横
			{
				swapSegment(2, 3);
			}

			rebuildingArea(4);
		}
		else {
			//五角形
			changePentagon(addPointNum[1] - addPointNum[0]);
			rebuildingArea(5);
		}
};

//切り取った後に面積を再構築する
void Wall::rebuildingArea(int corner) 
{
	//頂点座標設定
	std::vector<Vec2>vecs;
	for (int i = 0; i < corner;i++)
	vecs.push_back(segments[i].s);

	myWall->clear();
	myWall->drawPolygon(&vecs[0], corner, Color4F::WHITE, 1, Color4F::YELLOW);

	clipp->setStencil(myWall);

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

//間にある点をセグメントとして使う配列のソート(取り出す番地,ほしい配列番地)
void Wall::sortSegment(int pic,int target,int addNum) 
{
	SEGMENT temp = segments[pic];//コピー
	for (int i = pic; i > target; i--) 
	{
		segments[i] = segments[i - 1];//取り出す番地がほしい配列番地に行くまで代入
	}
	segments[target] = temp;//コピーしたやつをほしい配列番地に代入
	
	if(addNum!=-1)
	addPointNum[addNum] = target;

};

//セグメント入れ替え
void Wall::swapSegment(int one, int two) 
{
	SEGMENT s = segments[one];

	segments[one] = segments[two];
	segments[two] = s;

	segments[one].v = segments[one + 1].s;
	segments[two].v = segments[two + 1].s;
};
