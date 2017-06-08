#include "ObjectBase.h"

//�����ݒ�
void ObjectBase::initialize(Vec2 pos) 
{
	setPosition(pos);
	myPosition = pos;
};

//�L�����N�^�[p�Ƃ͈͉̔~���d�Ȃ��Ă��邩
bool ObjectBase::onCollision(ObjectBase* p)
{
	return false;
};

//pos���甼�arange���ɂ��邩
bool ObjectBase::onCollision(Vec2 pos, float range)
{
	if (length(pos - myPosition)*length(pos - myPosition) <= range)
	{
		////log("length=%f,range=%f",length(pos-myPosition),range);
		return true;
	}
	return false;
};

//start-end�Ԃɓ������Ă��邩�ǂ���
bool ObjectBase::onCollision(Vec2 start, Vec2 end,float range)
{
	Vec2 AB = end - start;
	Vec2 AP = myPosition - start;
	Vec2 BP = myPosition - end;

	//�O��
	float APxAB = cross(AB,AP);
	if (APxAB < 0)APxAB *= -1;

	//����
	float DotAP = dot(AP, AB);
	float DotBP = dot(BP, AB);

	if (AB.x*AB.x == 0 && AB.y*AB.y == 0)
	{
		log("out");
		return false;
	}
	float ans = APxAB / length(AB);

	if (ans < range)
	{
		if (DotAP*DotBP <= 0)
		{
			return true;
		}
		else
		{
			if (ans > length(AP) || ans>length(BP))
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


//�����蔻��̂�����̂�ݒ�
void ObjectBase::setTarget(ObjectBase* p)
{
	targets.pushBack(p);
};
