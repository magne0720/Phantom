#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "Wall.h"
#include "ObjectBase.h"

USING_NS_CC;


//�L�����N�^�[�̊��N���X�B
//�ړ��A�Փ˔���A�ړ����x�Ȃǂ̊�{���
class Character:public ObjectBase
{
public:
	static Character* create(Vec2 spawnPos, DIR_DEGREE dir = DIR_DEGREE::DIR_DOWN);
	//�����ݒ�
	virtual bool init(Vec2 spawnPos, DIR_DEGREE dir = DIR_DEGREE::DIR_DOWN);
	//�X�V
	virtual void update(float delta);
	//�����ݒ�
	void initialize(Vec2 pos,DIR_DEGREE dir);

	//�X�V����
	//-----------------------------------------
	//�L�����N�^�[�̊�{�s��
	void action();
	//�ǉ��s��
	virtual void plusAction();
	//�ړ�
	virtual void move(float plusSpeed=1.0f);
	//-----------------------------------------

	//���菈��
	//-----------------------------------------
	//��lastTargetPosition�ɂ��邩
	bool onLastTargetPosition(Vec2 pos);

	//�ڂ̑O���ǂ��ǂ���
	bool onWall(SEGMENT s0, SEGMENT s1);
	//�~�͈̔�
	bool onWall(SEGMENT s0, Vec2 pos, float range);
	//�ړ��\����
	bool onMoveRange(Point target);
	//�E���ɂ��邩
	bool onDirectionRight(const Vec2 target);
	//�����ɂ��邩
	bool onDirectionLeft(const Vec2 target);
	//�Փ˔���܂Ƃ�
	virtual void allCollision();
	//-----------------------------------------


	//�Q�b�^�[
	//-----------------------------------------

	//�����̎擾
	Vec2 getDirectionVector();
	//-----------------------------------------


	//�Z�b�^�[
	//-----------------------------------------
	//��ԕω�
	void setState(STATUS state);
	//�����蔻��̂�����̂�ݒ�
	//���łɂ���Ȃ�ǉ����Ȃ�
	void setTargetWall(Wall* p);
	//���x�̕ύX
	void setSpeed(float speed);
	//�ړ��\�͈͕ύX
	void setMoveRange(float range);
	//���F�͈͐ݒ�
	void setDoubtDgree(float range);
	//�ړ��ꏊ�ݒ�
	void setTargetPosition(Vec2 pos);
	//360�x�̌����ύX
	void setDirection(float degree);
	//360�x�̌����ύX
	void setDirection(DIR_DEGREE degree);
	//�����ɂ���Ă��炤�x�N�g���Ɛi�ޕ����łǂ���̕����ɉ�]���邩�����߂�
	void setEvasionWall(Vec2 wall, Vec2 target);
	//-----------------------------------------

	//�摜����

	//void changeTexture(DIR_DEGREE);

	//-----------------------------------------


	//�ړ��ҋ@��Ԃ��ǂ���
	bool isMoveWait;
	
	//���Ɍ������ꏊ�B����Ɍ��������߂Ɉړ����s���B
	Vec2 targetPosition;

	//���g�̌���
	float myDirection;
	//�ړ����x
	float moveSpeed;
	//�ړ��\�͈͔��a
	float moveRange;
	//���F�͈�
	float doubtDegree;

	//��
	Vector<Wall*> walls;
	//���g�̏��
	STATUS myState;
	//�Փ˔���̏����Ԋu��������^�C�}�[
	float colTimer;



	//�v���C���[�̑��삪�قȂ�̂ŉ��z��
	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);

};

#endif // !__CHARACTER_H__
