#ifndef __OBJECT_BASE_H__
#define __OBJECT_BASE_H__

#include "cocos2d.h"
#include "CharacterAnimation.h"
#include "AllTags.h"

USING_NS_CC;

class ObjectBase :public Node 
{
public:	
	//���g�Ɠ����蔻��̂��镨
	Vector<ObjectBase*> targets;



	//�����ݒ�
	void initialize(Vec2 pos);
	//�����摜�𒆐S�ɔz�u
	void initWithFileCenter(std::string name, Size chipSize = Size(100, 100));
	//�^�[�Q�b�g�͈͂ɓ����Ă��邩
	virtual bool onCollision(Vec2 pos, float range);
	//���g�ƈ���(����)�̉~����
	virtual bool onCollision(ObjectBase* p);
	//�ԊO������
	virtual bool onCollision(Vec2 start, Vec2 end,float range);
	//�����蔻��̂�����̂�ݒ�
	void setTarget(ObjectBase* p);


	//�ړ��\�͈͂������~��
	DrawNode* moveRangeSp;
	//���g�̉摜
	CharacterAnimation* mySprite;
	BlendFunc* blender;

	//���g�̏ꏊ
	Vec2 myPosition;

};


#endif //! __OBJECT_BASE_H__
