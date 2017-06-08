#include "Wall.h"

Wall* Wall::create(Vec2 spawnPos, int num)
{
	Wall *pRet = new Wall();
	if (pRet && pRet->init(spawnPos, num))
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

Wall* Wall::createWall()
{
	Wall *pRet = new Wall();
	if (pRet && pRet->init())
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

bool Wall::init()
{
	if (!Node::init())return false;

	setPosition(designResolutionSize*0.5f);
	myPosition = designResolutionSize*0.5f;

	mySprite = Sprite::create();
	mySprite->setTextureRect(Rect(0, 0, designResolutionSize.width, designResolutionSize.height));

	points[0] = Vec2(designResolutionSize.width*0.0f,designResolutionSize.height*0.0f);//左下
	points[1] = Vec2(designResolutionSize.width, designResolutionSize.height*0.0f);//右下
	points[2] = Vec2(designResolutionSize.width, designResolutionSize.height);//右上
	points[3] = Vec2(designResolutionSize.width*0.0f, designResolutionSize.height);//左上
	points[4] = Vec2(0, 0);//5角形になった時用
	points[5] = Vec2(0, 0);//分割時に必要になる

	myWall = DrawNode::create();
	myWall->setPosition(myWall->getPosition() - getPosition());

	debug = DrawNode::create();
	debug->setPosition(-getPosition());
	addChild(debug, 51);

	//頂点座標設定
	std::vector<Vec2>vecs;
	vecs.push_back(points[0]);
	vecs.push_back(points[1]);
	vecs.push_back(points[2]);
	vecs.push_back(points[3]);

	myWall->drawPolygon(&vecs[0], 4, Color4F::BLACK, 1, Color4F::YELLOW);
	myWall->setPosition(-getPosition());
	addChild(myWall);

	clipp = ClippingNode::create();
	addChild(clipp);


	isCuted = false;
	segmentCount = 4;
	drawCount = 0;
	scheduleUpdate();

	return true;
}

bool Wall::init(Vec2 spawnPos,int num) 
{
	if (!Node::init()) 
	{
		return false;
	}
	setPosition(spawnPos);
	myPosition = spawnPos;

	String* name = String::createWithFormat("wall%03d.png", num);

	mySprite = Sprite::create(name->getCString());
	//addChild(mySprite);

	Rect r = mySprite->getBoundingBox();

	points[0] = Vec2(r.getMinX() + spawnPos.x, r.getMinY() + spawnPos.y);//左
	points[1] = Vec2(r.getMinX() + spawnPos.x, r.getMaxY() + spawnPos.y);//上
	points[2] = Vec2(r.getMaxX() + spawnPos.x, r.getMaxY() + spawnPos.y);//右
	points[3] = Vec2(r.getMaxX() + spawnPos.x, r.getMinY() + spawnPos.y);//下
	points[4] = Vec2(0, 0);//5角形になった時用
	points[5] = Vec2(0, 0);//分割時に必要になる

	myWall = DrawNode::create();
	myWall->setPosition(myWall->getPosition() - spawnPos);

	debug = DrawNode::create();
	debug->setPosition(- spawnPos);
	addChild(debug,51);

	//頂点座標設定
	std::vector<Vec2>vecs;
	vecs.push_back(points[0]);
	vecs.push_back(points[1]);
	vecs.push_back(points[2]);
	vecs.push_back(points[3]);

	myWall->drawPolygon(&vecs[0], 4, Color4F::BLACK, 1, Color4F::YELLOW);
	myWall->setPosition(-spawnPos);
	addChild(myWall);

	clipp = ClippingNode::create();
	clipp->setStencil(myWall);
	clipp->addChild(mySprite);
	addChild(clipp);

	myWall->drawSegment(points[0], points[1], 5, Color4F::RED);
	myWall->drawSegment(points[1], points[2], 5, Color4F::RED);
	myWall->drawSegment(points[2], points[3], 5, Color4F::RED);
	myWall->drawSegment(points[3], points[0], 5, Color4F::RED);

	isCuted = false;
	segmentCount = 4;
	drawCount = 0;

	scheduleUpdate();

	return true;
};

void Wall::update(float delta) 
{
	if (*playerCut) 
	{
		callCollision();
	}

	cutTimer += 0.04f;
	if (cutTimer >= 1.0f) 
	{
		debug->clear();
		if (drawCount == 0) 
			debug->drawSegment(points[drawCount], getOverPoint(points, segmentCount, drawCount + 1), 5, Color4F::ORANGE);
		else
			debug->drawSegment(points[drawCount], getOverPoint(points, segmentCount, drawCount + 1), 5, Color4F::GREEN);
		drawCount++;
		cutTimer = 0;
		if (drawCount >= segmentCount)drawCount = 0;
	}
}

void Wall::setTargets(Vec2* from, Vec2* to) 
{
	fromPos = from;
	toPos = to;
};

//新しくポイントを設定する
void Wall::setPoint(int number, Vec2 point) 
{
//	points[number] = point;
};

//衝突判定命令
void Wall::callCollision()
{
	if (isCuted)return;
	Vec2 temp[POINT_SIZE];
	Vec2 pos;
	int count = segmentCount;
	for (int i = 0; i < POINT_SIZE; i++) {
		temp[i] = points[i];
	}

	for (int i = 0; i < count; i++)
	{
		//点が当たっているか
		if (checkPoint(&pos, SEGMENT(*fromPos, *toPos), SEGMENT(temp[i], getOverPoint(temp, count, i + 1))) == 1)
		{
			//点を追加
			i++;
			addPointNum[count - 4] = i;
			addPoint(&pos, temp, i);
			count++;
			if (count ==6)break;
		}
	}
	if (count == POINT_SIZE)
	{
		for (int i = 0; i < POINT_SIZE; i++){
			points[i] = temp[i];
		}

		isCuted = true;
		checkCutArea(points);
	}
};

//from-to間の線とtargetの交点を調べる
int Wall::checkPoint(Vec2* hitPos, SEGMENT s0, SEGMENT s1)
{
	//X軸方向のベクトルが0かどうか
	if (s0.to.x == 0.0f || s1.to.x == 0.0f) {
		if (s0.to.x == 0.0f&&s1.to.x == 0.0f)
			return 0;
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
		if ((t0<0.0f) || (t0>1.0f) || (t1 < 0.0f) || (t1 > 1.0f))return 0;
		if (hitPos) *hitPos = r;
		return 1;
	}
	else {
		//線分の傾きを求める
		float a0 = s0.to.y / s0.to.x;
		float a1 = s1.to.y / s1.to.x;

		//傾きが同一の場合は平行なので衝突しない
		if ((a0 == a1) || a0 == -a1)return 0;

		//交点のx,y座標を求める
		Vec2 r;
		r.x = (a0*s0.from.x - a1*s1.from.x + s1.from.y - s0.from.y) / (a0 - a1);
		r.y = a0*(r.x - s0.from.x) + s0.from.y;

		//交点が線分内にあるか調べる
		float t0 = (r.x - s0.from.x) / s0.to.x;		//t=0~1の時は線分s0内
		float t1 = (r.x - s1.from.x) / s1.to.x;		//t=0~1の時は線分s1内

		if ((t0<0.0f) || (t0>1.0f) || (t1<0.0f) || (t1>1.0f))return 0;

		//衝突していることを返す
		if (hitPos)*hitPos = r;
		return 1;
	}
};

//検出した点が含まれている線を検出した点を境に分割する
//hitPos=追加する点
//points=追加先の配列
//toNum=追加先の配列に入れたい番号
void Wall::addPoint(Vec2* hitPos, Vec2* points	,int toNum) 
{
	Vec2 point;
	point = *hitPos;
	for (int i =POINT_SIZE-1; i > toNum; i--) 
	{
		points[i] = points[i - 1];
	}
	points[toNum] = point;
};

//点の順番の入れ替え
void Wall::swapPoint(Vec2* points, int one, int two) 
{
	Vec2 temp = points[two];
	points[two] = points[one];
	points[one] = temp;
};

//配列の中を先頭から3つずつ取り出した点で面積の合計を返す
float Wall::sumArea(Vec2 points[],int point[]) 
{
	float area = 0;
	for (int i = 0; point[i+2] != -1; i++) 
	{
		area += (length(points[point[i]] - points[point[i+1]])+ length(points[point[i+1]] - points[point[i+2]])+ length(points[point[i+2]] - points[point[i]]))/2;
	}
	return area;
};

//角の頂点をなくして、その頂点をつないでいた線同士をつないだ5角形を作る
void Wall::changePentagon(Vec2 *vPoint, int onePoint, int twoPoint)
{
	Vec2* from=vPoint;
	int pointNum;
	//頂点がなくなるので、その前の点とそのあとの点をつなぐ
	if ((onePoint + 1 )% 5 == (twoPoint - 1) % 5) 
	{
		pointNum = (onePoint + 1) % 5;
	}
	//いらない頂点を消す
	for (int i = pointNum; i < 5; i++) 
	{
		vPoint[i] = vPoint[i + 1];
	}
};

//切り取る場所検出
void Wall::checkCutArea(Vec2* points)
{
	int right[POINT_SIZE], left[POINT_SIZE];
	int rightcount = 0, leftcount = 0;
	for (int i = 0; i < POINT_SIZE; i++) {
		if (i != addPointNum[0] && i != addPointNum[1])
			//追加した二つの点でできた線の右側かどうか
			if (cross(points[addPointNum[0]] - points[addPointNum[1]], points[addPointNum[0]] - points[i])>0)
			{
				right[rightcount] = i;
				rightcount++;
			}
			else {
				left[leftcount] = i;
				leftcount++;
			}
	}
	//分割線を追加
	right[rightcount++] = addPointNum[0];
	right[rightcount++] = addPointNum[1];
	right[rightcount] = -1;//NULLコード

	left[leftcount++] = addPointNum[0];
	left[leftcount++] = addPointNum[1];
	left[leftcount] = -1;//NULLコード

		//結果が四角形になる場合
	if (rightcount == 4 && leftcount == 4)
	{		
		//log("box");
		//面積比を見る
		if (sumArea(points, right) > sumArea(points, left))
		{
			sortPoints(points, right);
		}
		else
		{
			sortPoints(points, left);
		}
		//構築
		rebuildingArea(points, 4);
	}
	else {
		//五角形
		if (rightcount > leftcount)
		{
			//右側で描画
			sortPoints(points, right);
		}
		else {
			//左側で描画
			sortPoints(points,left);
		}
		//構築
		rebuildingArea(points, 5);
	}
	for (int i = 0; i < segmentCount; i++)
	{
		//log("[%d][%f,%f]", i, points[i].x, points[i].y);
	}
};

//切り取った後に面積を再構築する
void Wall::rebuildingArea(Vec2 points[], int corner)
{
	//log("rebuild-%d", corner);
	//頂点座標設定
	std::vector<Vec2>vecs;
	for (int i = 0; i < corner; i++) {
		vecs.push_back(points[i]);
	}
	myWall->clear();
	myWall->drawPolygon(&vecs[0], corner, Color4F::BLUE, 4, Color4F::GRAY);

	clipp->setStencil(myWall);

	segmentCount = corner;
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

//順番を右回りに戻す
void Wall::sortPoints(Vec2* points, int*nums) 
{
	int temp;
	Vec2 pos;

	for (int i = 0; nums[i] != -1; i++)
		//log("points[%d][%f,%f]", nums[i], points[nums[i]].x, points[nums[i]].y);

	for (int i = 0; nums[i] != -1; i++) 
		for (int j = i; nums[j] != -1; j++)
		{
			if (nums[i] > nums[j]) 
			{
				//入れ替え
				//log("change");
				temp = nums[i];
				nums[i] = nums[j];
				nums[j] = temp;
			}
		}
	for (int i = 0; nums[i] != -1; i++)
	{
		//log("i=%d!=%d", i, nums[i]);
		pos = points[i];
		points[i] = points[nums[i]];
		points[nums[i]] = pos;
	}
};


//壁の配列が規定より超えたときに超えた分だけ0から数える
Vec2 Wall::getOverPoint(Vec2 points[],int limit,int num) 
{
	int c=num;
	if (limit == 0)return points[c];

	if (num >= limit)
	{
		c = num%limit;
	//	//log("%d/%d=%d...%d", num, limit,num/limit, num%limit);
	}
	return points[c];
};

//選択点と次の点との方向ベクトルを返す
Vec2 Wall::getSegment(int startpoint) 
{
	Vec2 pos;
	pos = getOverPoint(points, segmentCount, startpoint+1)-points[startpoint];
	return pos;
};

