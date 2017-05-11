#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "AllTags.h"
#include "Wall.h"

USING_NS_CC;


//�L�����N�^�[�̊��N���X�B
//�ړ��A�Փ˔���A�ړ����x�Ȃǂ̊�{���
class Character:public Node
{
public:
	static Character* create(Vec2 spawnPos);
	//�����摜�𒆐S�ɔz�u
	void initWithFileCenter(std::string name);
	//�����ݒ�
	virtual bool init(Vec2 spawnPos);
	//�X�V
	virtual void update(float delta);
	//�����ݒ�
	void initialize(Vec2 pos);



	
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
	//�^�[�Q�b�g�͈͂ɓ����Ă��邩
	virtual bool onCollision(Vec2 pos,float range);
	//���g�ƈ���(����)�̉~����
	virtual bool onCollision(Character* p);
	//�ԊO������
	virtual bool onCollision(Vec2 start, Vec2 end);
	//�ړ��\����
	bool onMoveRange(Point target);
	//�E���ɂ��邩
	bool onDirectionRight(const Vec2 target);
	//�����ɂ��邩
	bool onDirectionLeft(const Vec2 target);
	//�i�ޕ������ǂ��ǂ���
	bool onWall(Vector<Wall*> quad);
	//�Փ˔���܂Ƃ�
	virtual void allCollision();
	//-----------------------------------------


	//�Q�b�^�[
	//-----------------------------------------

	//�����x�N�g������w��p�x�Ŏ��g�̎��F�͈͂̃x�N�g�����擾����
	Vec2 getDirectionDegree(Vec2 target, float deg, float range = 1.0f);
	//�����̎擾
	Vec2 getDirectionVector();
	//-----------------------------------------


	//�Z�b�^�[
	//-----------------------------------------
	//��ԕω�
	void setState(STATUS state);
	//�����蔻��̂�����̂�ݒ�
	void setTarget(Character* p);
	//�����蔻��̂�����̂�ݒ�
	void setTarget(Wall* p);
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
	//�����ɂ���Ă��炤�x�N�g���Ɛi�ޕ����łǂ���̕����ɉ�]���邩�����߂�
	void setEvasionWall(Vec2 wall, Vec2 target);
	//-----------------------------------------

	
	//�v�Z����
	//-----------------------------------------
	//���K��
	Vec2 normalize(Vec2 pos);
	//����
	float dot(Vec2 from, Vec2 to);
	//����
	float length(Vec2 pos);
	//-----------------------------------------


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
	//�\�肳�ꂽ�ŏI�ꏊ�B�����ɂ��܂ňړ�����B
	Vec2 lastTargetPosition;

	//���g�̌���
	float myDirection;
	//�ړ����x
	float moveSpeed;
	//�ړ��\�͈͔��a
	float moveRange;
	//���F�͈�
	float doubtDegree;
	//���g�Ɠ����蔻��̂��镨
	Vector<Character*> targets;
	//��
	Vector<Wall*> walls;
	//���g�̏��
	STATUS myState;




	//�v���C���[�̑��삪�قȂ�̂ŉ��z��
	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);

};

#endif // !__CHARACTER_H__
