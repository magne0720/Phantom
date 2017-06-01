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

	segments[0] = SEGMENT(Vec2(r.getMinX() + spawnPos.x, r.getMinY() + spawnPos.y), Vec2(r.getMinX()+spawnPos.x, r.getMaxY() + spawnPos.y));//��
	segments[1] = SEGMENT(Vec2(r.getMinX() + spawnPos.x, r.getMaxY() + spawnPos.y), Vec2(r.getMaxX()+spawnPos.x, r.getMaxY() + spawnPos.y));//��
	segments[2] = SEGMENT(Vec2(r.getMaxX() + spawnPos.x, r.getMaxY() + spawnPos.y), Vec2(r.getMaxX()+spawnPos.x, r.getMinY() + spawnPos.y));//�E
	segments[3] = SEGMENT(Vec2(r.getMaxX() + spawnPos.x, r.getMinY() + spawnPos.y), Vec2(r.getMinX()+spawnPos.x, r.getMinY() + spawnPos.y));//��
	segments[4] = SEGMENT(Vec2(0, 0), Vec2(0, 0));//5�p�`�ɂȂ������p
	segments[5] = SEGMENT(Vec2(0, 0), Vec2(0, 0));//�������ɕK�v�ɂȂ�


	myWall = DrawNode::create();
	myWall->setPosition(myWall->getPosition() - spawnPos);

	//���_���W�ݒ�
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

//�V�����|�C���g��ݒ肷��
void Wall::setPoint(int number, Vec2 point) 
{
//	segments[number] = point;
};

//�Փ˔��薽��
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

//from-to�Ԃ̐���target�̌�_�𒲂ׂ�
int Wall::checkPoint(Vec2* hitPos, SEGMENT s0, SEGMENT s1)
{
	//X�������̃x�N�g����0���ǂ���
	if (s0.v.x == 0.0f || s1.v.x == 0.0f) {
		if (s0.v.x == 0.0f&&s1.v.x == 0.0f)
			return 0;
		//���s

		Vec2 r;
		float t0, t1;
		if (s0.v.x == 0.0f) {
			r.x = s0.s.x;
			r.y = (s1.v.y / s1.v.x)*(r.x - s1.s.x) + s1.s.y;

			t0 = (r.y - s0.s.y) / s0.v.y;		//t=0~1�̎��͐���s0��
			t1 = (r.x - s1.s.x) / s1.v.x;		//t=0~1�̎��͐���s1��
		}
		else {
			r.x = s1.s.x;
			r.y = (s0.v.y / s0.v.x)*(r.x - s0.s.x) + s0.s.y;

			t0 = (r.x - s0.s.x) / s0.v.x;		//t=0~1�̎��͐���s0��
			t1 = (r.y - s1.s.y) / s1.v.y;		//t=0~1�̎��͐���s1��
		}
		if ((t0<0.0f) || (t0>1.0f) || (t1 < 0.0f) || (t1 > 1.0f))return 0;
		if (hitPos) *hitPos = r;
		return 1;
	}
	else {
		//�����̌X�������߂�
		float a0 = s0.v.y / s0.v.x;
		float a1 = s1.v.y / s1.v.x;

		//�X��������̏ꍇ�͕��s�Ȃ̂ŏՓ˂��Ȃ�
		if ((a0 == a1) || a0 == -a1)return 0;

		//��_��x,y���W�����߂�
		Vec2 r;
		r.x = (a0*s0.s.x - a1*s1.s.x + s1.s.y - s0.s.y) / (a0 - a1);
		r.y = a0*(r.x - s0.s.x) + s0.s.y;

		//��_���������ɂ��邩���ׂ�
		float t0 = (r.x - s0.s.x) / s0.v.x;		//t=0~1�̎��͐���s0��
		float t1 = (r.x - s1.s.x) / s1.v.x;		//t=0~1�̎��͐���s1��

		if ((t0<0.0f) || (t0>1.0f) || (t1<0.0f) || (t1>1.0f))return 0;

		//�Փ˂��Ă��邱�Ƃ�Ԃ�
		if (hitPos)*hitPos = r;
		return 1;
	}
};

//���o�����_���܂܂�Ă���������o�����_�����ɕ�������
void Wall::cutSegment(Vec2* hitPos, SEGMENT& from, SEGMENT& out) 
{
	SEGMENT seg;

	seg.v = from.v-*hitPos+from.s;
	seg.s = *hitPos;

	from.v = seg.s;
	out = seg;
};

//�z��̒���擪����3�����o�����_�Ŗʐς̍��v��Ԃ�
float Wall::sumArea(int point[]) 
{
	float area = 0;
	for (int i = 0; point[i+2] != -1; i++) 
	{
		area += (length(segments[point[i]].s - segments[point[i+1]].s)+ length(segments[point[i+1]].s - segments[point[i+2]].s)+ length(segments[point[i+2]].s - segments[point[i]].s))/2;
	}
	return area;
};

//�p�̒��_���Ȃ����āA���̒��_���Ȃ��ł��������m���Ȃ���5�p�`�����
void Wall::changePentagon(int pointNum) 
{
	SEGMENT s[6];
	//���_���Ȃ��Ȃ�̂ŁA���̑O�̓_�Ƃ��̂��Ƃ̓_���Ȃ�
	segments[pointNum - 1].v = segments[pointNum + 1].s;
	//����Ȃ����_������
	for (int i = pointNum; i < 5; i++) 
	{
		segments[i] = segments[i + 1];
	}
	////6�Ԗڂ͎g��Ȃ��̂ŏ�����
	//segments[5] = SEGMENT(Vec2(0, 0), Vec2(0, 0));
};

//�؂���ꏊ���o
void Wall::checkCutArea()
{
	SEGMENT sSeg[6];
	int right[6], left[6];
	int rightcount = 0, leftcount = 0;
	for (int i = 0; i < 6; i++) {
		if (i != addPointNum[0] && i != addPointNum[1])
			//�ǉ�������̓_�łł������̉E�����ǂ���
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
		//���ʂ��l�p�`�ɂȂ�ꍇ
		if (rightcount == 2 && leftcount == 2)
		{
			//��������ǉ�
			right[rightcount++] = addPointNum[0];
			right[rightcount++] = addPointNum[1];
			right[rightcount] = -1;//NULL�R�[�h

			left[leftcount++] = addPointNum[0];
			left[leftcount++] = addPointNum[1];
			left[leftcount] = -1;//NULL�R�[�h


			//�ʐϔ������
			if (sumArea(right) > sumArea(left))
			{
				//������������
				for (int j = 0; right[j]!=-1; j++) 
				{
					sSeg[j] = segments[right[j]];
				}
			}
			else 
			{
				//�E����������
				for (int j = 0; left[j] != -1; j++)
				{
					sSeg[j] = segments[left[j]];
				}
			}

			//segments[4] = SEGMENT(Vec2(0, 0), Vec2(0, 0));//����Ȃ��Ȃ����ꏊ
			//segments[5] = SEGMENT(Vec2(0, 0), Vec2(0, 0));//����Ȃ��Ȃ����ꏊ


			for (int w = 0; w < 6; w++) 
			{
				segments[w] = sSeg[w];
			//	log("[%d]=[%f,%f]", w, segments[w].s.x, segments[w].s.y);
			}

			if (addPointNum[0] ==1)//��
			{
				swapSegment(2, 3);
			}

			rebuildingArea(4);
		}
		else {
			//�܊p�`
			changePentagon(addPointNum[1] - addPointNum[0]);
			rebuildingArea(5);
		}
};

//�؂�������ɖʐς��č\�z����
void Wall::rebuildingArea(int corner) 
{
	//���_���W�ݒ�
	std::vector<Vec2>vecs;
	for (int i = 0; i < corner;i++)
	vecs.push_back(segments[i].s);

	myWall->clear();
	myWall->drawPolygon(&vecs[0], corner, Color4F::WHITE, 1, Color4F::YELLOW);

	clipp->setStencil(myWall);

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

//�Ԃɂ���_���Z�O�����g�Ƃ��Ďg���z��̃\�[�g(���o���Ԓn,�ق����z��Ԓn)
void Wall::sortSegment(int pic,int target,int addNum) 
{
	SEGMENT temp = segments[pic];//�R�s�[
	for (int i = pic; i > target; i--) 
	{
		segments[i] = segments[i - 1];//���o���Ԓn���ق����z��Ԓn�ɍs���܂ő��
	}
	segments[target] = temp;//�R�s�[��������ق����z��Ԓn�ɑ��
	
	if(addNum!=-1)
	addPointNum[addNum] = target;

};

//�Z�O�����g����ւ�
void Wall::swapSegment(int one, int two) 
{
	SEGMENT s = segments[one];

	segments[one] = segments[two];
	segments[two] = s;

	segments[one].v = segments[one + 1].s;
	segments[two].v = segments[two + 1].s;
};
