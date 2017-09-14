#ifndef __OBJECT_BASE_H__
#define __OBJECT_BASE_H__

#include "cocos2d.h"
#include "CharacterAnimation.h"
#include "AllTags.h"

USING_NS_CC;

//�I�u�W�F�N�g���ׂĂɂ���@�\
//�����Ĉړ�����@�\�͎����Ȃ�
//���݂��̏Փ˔���͂���\��
class ObjectBase :public Node 
{
public:	

	//�����ݒ�
	void initialize(Vec2 pos);
	//�����摜�𒆐S�ɔz�u
	void initWithFileCenter(std::string body, std::string head, Size chipSize = Size(100, 100));
	//�^�[�Q�b�g�͈͂ɓ����Ă��邩
	virtual bool onCollision(Vec2 pos, float range);
	//���g�ƈ���(����)�̉~����
	virtual bool onCollision(ObjectBase* p);
	//�ԊO������
	virtual bool onCollision(Vec2 start, Vec2 end,float range);
	//�����蔻��̂�����̂�ݒ�
	void setTarget(ObjectBase* p);
	//�Փ˔͈͂̐ݒ�
	void setObjectRange(float range);

	//�ړ��\�͈͂������~��
	DrawNode* moveRangeSp;
	//���g�̉摜
	CharacterAnimation* mySprite;
	//���g�̏ꏊ
	Vec2 myPosition;


	//���g�Ɠ����蔻��̂��镨
	Vector<ObjectBase*> targets;

	float objectRange;//�Փ˔͈�
};


#endif //! __OBJECT_BASE_H__
