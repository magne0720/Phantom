#include "ObjectBase.h"

//�����ݒ�
void ObjectBase::initialize(Vec2 pos) 
{
	setPosition(pos);
	myPosition = pos;
};

//�摜�𒆉��ɂ��Ď��g�̉摜��u��
void ObjectBase::initWithFileCenter(std::string body, std::string head, Size chipSize)
{
	mySprite = CharacterAnimation::create(body, head,chipSize, 0.5f);
	addChild(mySprite, 5);
};

//�L�����N�^�[p�Ƃ͈͉̔~���d�Ȃ��Ă��邩
bool ObjectBase::onCollision(ObjectBase* p)
{
	return onCollisionCircle(this->myPosition, this->objectRange, p->myPosition, p->objectRange);
};

//pos���甼�arange���ɂ��邩
bool ObjectBase::onCollision(Vec2 pos, float range)
{
	if (length(pos - myPosition) <= range)
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

void ObjectBase::setObjectRange(float range) 
{
	objectRange = range;
}

