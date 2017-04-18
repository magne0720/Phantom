#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "AllTags.h"

USING_NS_CC;


//�L�����N�^�[�̊��N���X�B
//�ړ��A�Փ˔���A�ړ����x�Ȃǂ̊�{���
class Character:public Node
{
public:
	
	static Character* create(Vec2 spawnPos);
	void initWithFileCenter(std::string name);
	//�����ݒ�
	virtual bool init(Vec2 spawnPos);
	//��{�I�Ɉړ��Ǘ��݂̂Ȃ̂Ōp������K�v���Ȃ������B
	void update(float delta);
	//�ړ��\����
	bool canMoveRange(Point target);
	//�e�L�����N�^�[�̍s��
	virtual void action();
	//�ړ�
	virtual void move();
	//�Փ˔���
	virtual void onCollision(float deg);
	//�ړ��\�͈͕ύX
	void setMoveRange(float range);
	//�����ύX
	void setDirection(float seta);

	//�ړ��ҋ@��Ԃ��ǂ���
	bool isMoveWait;
	//�ړ��\�͈͂������~��
	DrawNode* moveRangeSp;
	//���g�̉摜
	Sprite* mySprite;
	//���g�̏ꏊ
	Vec2 myPosition;
	//���Ɍ������ꏊ�B����Ɍ��������߂Ɉړ����s���B
	Vec2 targetPosition;
	//������ێ�����
	DIRECTION myDirection;
	//�ړ����x
	float moveSpeed;
	//�ړ��\�͈͔��a
	float moveRange;

	//�v���C���[�̑��삪�قȂ�̂ŉ��z��
	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);

};

#endif // !__CHARACTER_H__
