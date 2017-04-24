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
	//�X�V
	virtual void update(float delta);
	//�ړ��\����
	bool canMoveRange(Point target);
	//�e�L�����N�^�[�̍s��
	virtual void action();
	//�ړ�
	virtual void move();
	//�Փ˔���
	virtual bool onCollision(float deg);
	//�ԊO������
	virtual bool onCollision(Vec2 start, Vec2 end);
	//���x�̕ύX
	void setSpeed(float speed);
	//�ړ��\�͈͕ύX
	void setMoveRange(float range);
	//�����ύX
	void setDirection(float seta,float alpha=1.0f);
	//�����擾
	Vec2 getDirectionVector(Vec2 target,float range=1.0f);
	//�����x�N�g������w��p�x�Ŏ��g�̎��F�͈͂̃x�N�g�����擾����
	Vec2 getDirectionDegree(float deg, float range = 1.0f);
	//�E���ɂ��邩
	bool getDirectionRight(Vec2 target);
	//�����ɂ��邩
	bool getDirectionLeft(Vec2 target);


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
	//���g�̌���
	DIR_DEGREE myDirection;
	//�ړ����x
	float moveSpeed;
	//�ړ��\�͈͔��a
	float moveRange;
	//���F�͈�
	float doubtDegree;

	//�v���C���[�̑��삪�قȂ�̂ŉ��z��
	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);

};

#endif // !__CHARACTER_H__
