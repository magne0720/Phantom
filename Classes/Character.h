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
	//�����蔻��̂�����̂�ݒ�
	void setTarget(Character* p);
	//�����蔻��̂�����̂�ݒ�
	void setTarget(Wall* p);
	//�����擾
	Vec2 getDirectionVector(Vec2 target,float range=1.0f);
	//�����x�N�g������w��p�x�Ŏ��g�̎��F�͈͂̃x�N�g�����擾����
	Vec2 changeDirectionDegree(Vec2 target,float deg, float range = 1.0f);
	//�E���ɂ��邩
	bool getDirectionRight(Vec2 target);
	//�����ɂ��邩
	bool getDirectionLeft(Vec2 target);
	//�i�ޕ������ǂ��ǂ���
	bool checkWall(Vector<Wall*> quad);
	//�����ɂ���Ă��炤�x�N�g���Ɛi�ޕ����łǂ���̕����ɉ�]���邩�����߂�
	void checkEvasionWall(Vec2 wall, Vec2 target);
	//��ԕω�
	void setState(STATUS state);
	//���K��
	Vec2 normalize(Vec2 pos);
	//����
	float dot(Vec2 from, Vec2 to);
	//����
	float length(Vec2 pos);


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
