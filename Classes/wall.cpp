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

	mySprite = Sprite::create("sphere.png");
	//addChild(mySprite);

	Rect r = mySprite->getBoundingBox();

	points[0] = Vec2(r.getMinX() + spawnPos.x, r.getMinY() + spawnPos.y);//��
	points[1] = Vec2(r.getMinX() + spawnPos.x, r.getMaxY() + spawnPos.y);//��
	points[2] = Vec2(r.getMaxX() + spawnPos.x, r.getMaxY() + spawnPos.y);//�E
	points[3] = Vec2(r.getMaxX() + spawnPos.x, r.getMinY() + spawnPos.y);//��
	points[4] = Vec2(0, 0);//5�p�`�ɂȂ������p
	points[5] = Vec2(0, 0);//�������ɕK�v�ɂȂ�

	myWall = DrawNode::create();
	myWall->setPosition(myWall->getPosition() - spawnPos);

	debug = DrawNode::create();
	debug->setPosition(- spawnPos);
	addChild(debug,51);

	//���_���W�ݒ�
	std::vector<Vec2>vecs;
	vecs.push_back(points[0]);
	vecs.push_back(points[1]);
	vecs.push_back(points[2]);
	vecs.push_back(points[3]);

	myWall->drawPolygon(&vecs[0], 4, Color4F::WHITE, 1, Color4F::YELLOW);
	myWall->setPosition(-spawnPos);
	addChild(myWall,50);

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

	for (int i = 0; i < 6;i++)
	{
		log("initPos[%d],[%f,%f]", i, points[i].x, points[i].y);
	}

	scheduleUpdate();

	return true;
};

void Wall::update(float delta) 
{
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

//�V�����|�C���g��ݒ肷��
void Wall::setPoint(int number, Vec2 point) 
{
//	points[number] = point;
};

//�Փ˔��薽��
void Wall::callCollision()
{
	if (isCuted)return;
	Vec2 temp[POINT_SIZE];
	Vec2 pos;
	int count = segmentCount;
	for (int i = 0; i < POINT_SIZE; i++) {
		temp[i] = points[i];
		log("temp[%d]=[%f,%f]",i,temp[i].x,temp[i].y);
	}

	for (int i = 0; i < count; i++)
	{
		//�_���������Ă��邩
		if (checkPoint(&pos, SEGMENT(*fromPos, *toPos), SEGMENT(temp[i], getOverPoint(temp, count, i + 1))) == 1)
		{
			//�_��ǉ�
			log("num=[%d],hit[%f,%f]", i,pos.x,pos.y);
			i++;
			addPointNum[count - 4] = i;
			addPoint(&pos, temp, i);
			count++;
			if (count ==6)break;
		}
	}
	log("count=[%d]", count);

	if (count == POINT_SIZE)
	{
		for (int i = 0; i < POINT_SIZE; i++){
			points[i] = temp[i];
			log("after-temp[%d]=[%f,%f]", i, temp[i].x,temp[i].y);
		}

		isCuted = true;
		checkCutArea(points);
	}
};

//from-to�Ԃ̐���target�̌�_�𒲂ׂ�
int Wall::checkPoint(Vec2* hitPos, SEGMENT s0, SEGMENT s1)
{
	//X�������̃x�N�g����0���ǂ���
	if (s0.to.x == 0.0f || s1.to.x == 0.0f) {
		if (s0.to.x == 0.0f&&s1.to.x == 0.0f)
			return 0;
		//���s

		myWall->drawSegment(s0.from, s1.from, 4, Color4F::ORANGE);

		Vec2 r;
		float t0, t1;
		if (s0.to.x == 0.0f) {
			r.x = s0.from.x;
			r.y = (s1.to.y / s1.to.x)*(r.x - s1.from.x) + s1.from.y;

			t0 = (r.y - s0.from.y) / s0.to.y;		//t=0~1�̎��͐���s0��
			t1 = (r.x - s1.from.x) / s1.to.x;		//t=0~1�̎��͐���s1��
		}
		else {
			r.x = s1.from.x;
			r.y = (s0.to.y / s0.to.x)*(r.x - s0.from.x) + s0.from.y;

			t0 = (r.x - s0.from.x) / s0.to.x;		//t=0~1�̎��͐���s0��
			t1 = (r.y - s1.from.y) / s1.to.y;		//t=0~1�̎��͐���s1��
		}
		if ((t0<0.0f) || (t0>1.0f) || (t1 < 0.0f) || (t1 > 1.0f))return 0;
		if (hitPos) *hitPos = r;
		return 1;
	}
	else {
		//�����̌X�������߂�
		float a0 = s0.to.y / s0.to.x;
		float a1 = s1.to.y / s1.to.x;

		//�X��������̏ꍇ�͕��s�Ȃ̂ŏՓ˂��Ȃ�
		if ((a0 == a1) || a0 == -a1)return 0;

		//��_��x,y���W�����߂�
		Vec2 r;
		r.x = (a0*s0.from.x - a1*s1.from.x + s1.from.y - s0.from.y) / (a0 - a1);
		r.y = a0*(r.x - s0.from.x) + s0.from.y;

		//��_���������ɂ��邩���ׂ�
		float t0 = (r.x - s0.from.x) / s0.to.x;		//t=0~1�̎��͐���s0��
		float t1 = (r.x - s1.from.x) / s1.to.x;		//t=0~1�̎��͐���s1��

		if ((t0<0.0f) || (t0>1.0f) || (t1<0.0f) || (t1>1.0f))return 0;

		//�Փ˂��Ă��邱�Ƃ�Ԃ�
		if (hitPos)*hitPos = r;
		return 1;
	}
};

//���o�����_���܂܂�Ă���������o�����_�����ɕ�������
//hitPos=�ǉ�����_
//points=�ǉ���̔z��
//toNum=�ǉ���̔z��ɓ��ꂽ���ԍ�
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

//�_�̏��Ԃ̓���ւ�
void Wall::swapPoint(Vec2* points, int one, int two) 
{
	Vec2 temp = points[two];
	points[two] = points[one];
	points[one] = temp;
};

//�z��̒���擪����3�����o�����_�Ŗʐς̍��v��Ԃ�
float Wall::sumArea(Vec2 points[],int point[]) 
{
	float area = 0;
	for (int i = 0; point[i+2] != -1; i++) 
	{
		area += (length(points[point[i]] - points[point[i+1]])+ length(points[point[i+1]] - points[point[i+2]])+ length(points[point[i+2]] - points[point[i]]))/2;
	}
	return area;
};

//�p�̒��_���Ȃ����āA���̒��_���Ȃ��ł��������m���Ȃ���5�p�`�����
void Wall::changePentagon(Vec2 *vPoint, int onePoint, int twoPoint)
{
	Vec2* from=vPoint;
	int pointNum;
	//���_���Ȃ��Ȃ�̂ŁA���̑O�̓_�Ƃ��̂��Ƃ̓_���Ȃ�
	if ((onePoint + 1 )% 5 == (twoPoint - 1) % 5) 
	{
		pointNum = (onePoint + 1) % 5;
		log("ans[%d]",pointNum);
	}
	//����Ȃ����_������
	for (int i = pointNum; i < 5; i++) 
	{
		vPoint[i] = vPoint[i + 1];
	}
};

//�؂���ꏊ���o
void Wall::checkCutArea(Vec2* points)
{
	//Vec2 sPoint[POINT_SIZE];
	int right[POINT_SIZE], left[POINT_SIZE];
	int rightcount = 0, leftcount = 0;
	log("addPointNum=[%d]and[%d]", addPointNum[0], addPointNum[1]);
	for (int i = 0; i < POINT_SIZE; i++) {
		if (i != addPointNum[0] && i != addPointNum[1])
			//�ǉ�������̓_�łł������̉E�����ǂ���
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
	//��������ǉ�
	right[rightcount++] = addPointNum[0];
	right[rightcount++] = addPointNum[1];
	right[rightcount] = -1;//NULL�R�[�h

	left[leftcount++] = addPointNum[0];
	left[leftcount++] = addPointNum[1];
	left[leftcount] = -1;//NULL�R�[�h

		//���ʂ��l�p�`�ɂȂ�ꍇ
	if (rightcount == 4 && leftcount == 4)
	{		
		log("box");
		//�ʐϔ������
		if (sumArea(points, right) > sumArea(points, left))
		{
			log("left");
			//������������
			//for (int j = 0; right[j] != -1; j++)
			//{
			//	sPoint[j] = points[right[j]];
			//}
			sortPoints(points, left);
			//swapPoint(sPoint, 2, 3);
		}
		else
		{
			log("right");
			//�E����������
			//for (int j = 0; left[j] != -1; j++)
			//{
			//	sPoint[j] = points[left[j]];
			//}
			//if (addPointNum[0] == 0)//��
			//	swapPoint(sPoint, 2, 3);
			sortPoints(points, right);
		}
		//for (int w = 0; w < POINT_SIZE; w++)
		//{
		//	points[w] = sPoint[w];
		//}
		rebuildingArea(points, 4);
	}
	else {
		log("pentagon");
		if (rightcount > leftcount)
		{
			log("right");
			////�E���ŕ`��
			sortPoints(points, right);
			for (int j = 0; right[j] != -1; j++)
			{
				//sPoint[j] = points[right[j]];
			}
		}
		else {
			log("left");
			//�����ŕ`��
			sortPoints(points,left);
			for (int j = 0; left[j] != -1; j++)
			{
				//sPoint[j] = points[left[j]];
			}
		}
		//for (int w = 0; w < POINT_SIZE; w++)
		//{
		//	points[w] = sPoint[w];
		//}
		
		//�܊p�`
		rebuildingArea(points, 5);
	}
	for (int i = 0; i < segmentCount; i++)
	{
		log("[%d][%f,%f]", i, points[i].x, points[i].y);
	}
};

//�؂�������ɖʐς��č\�z����
void Wall::rebuildingArea(Vec2 points[], int corner)
{
	log("rebuild-%d", corner);
	//���_���W�ݒ�
	std::vector<Vec2>vecs;
	for (int i = 0; i < corner; i++) {
		vecs.push_back(points[i]);
	}
	myWall->clear();
	myWall->drawPolygon(&vecs[0], corner, Color4F::BLUE, 4, Color4F::GRAY);

	clipp->setStencil(myWall);

	segmentCount = corner;
};



//�؂����鉉�o
void Wall::cutEffect()
{

};

//start-end�Ԃɓ������Ă��邩�ǂ���
bool Wall::onCollision(Vec2 start, Vec2 end)
{
	Vec2 AB = end - start;
	Vec2 AP = myPosition - start;
	Vec2 BP = myPosition - end;

	//�O��
	float APxAB = AB.x*AP.y - AP.x*AB.y;
	if (APxAB < 0)APxAB = APxAB*(-1);

	//����
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

//���Ԃ��E���ɖ߂�
void Wall::sortPoints(Vec2* points, int*nums) 
{
	int temp;
	Vec2 pos;

	for (int i = 0; nums[i] != -1; i++)
		log("points[%d][%f,%f]", nums[i], points[nums[i]].x, points[nums[i]].y);

	for (int i = 0; nums[i] != -1; i++) 
		for (int j = i; nums[j] != -1; j++)
		{
			if (nums[i] > nums[j]) 
			{
				//����ւ�
				log("change");
				temp = nums[i];
				nums[i] = nums[j];
				nums[j] = temp;
			}
		}
	for (int i = 0; nums[i] != -1; i++)
	{
		log("i=%d!=%d", i, nums[i]);
		pos = points[i];
		points[i] = points[nums[i]];
		points[nums[i]] = pos;
	}
};


//�ǂ̔z�񂪋K���蒴�����Ƃ��ɒ�����������0���琔����
Vec2 Wall::getOverPoint(Vec2 points[],int limit,int num) 
{
	int c=num;
	if (limit == 0)return points[c];

	if (num >= limit)
	{
		c = num%limit;
	//	log("%d/%d=%d...%d", num, limit,num/limit, num%limit);
	}
	return points[c];
};
