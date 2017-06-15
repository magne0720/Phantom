#ifndef __PLAYER_ROBOT_H__
#define __PLAYER_ROBOT_H__

#include "cocos2d.h"
#include "Character.h"

#define MODE 0

USING_NS_CC;

//�Ȃ����������Ɉړ�������
//
class PlayerRobot :public Character 
{
public:
	static PlayerRobot* create(Vec2 pos);
	bool init(Vec2 pos);

	void plusAction();

	//�p�x�̕ۑ�
	void setAngle(Vec2 from, Vec2 to);
	//���ɍs���ׂ��Ƃ���̐ݒ�
	void nextPosition();
	//���ɍs���ꏊ���Ȃ��Ȃ������ɔz��̒����폜���A�������~�߂�
	void stopPosition();
	//��Α���
	void nextPositionB();
	void stopPositionB();

	//�v���C���[�̑��삪�قȂ�̂ŉ��z��
	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);


	//�ݒ莞�̃X�^�[�g�ʒu
	Vec2 startPosition;
	//����Ԓ������ʒu
	Vec2 endPosition;
	//
	Vec2 touchPosition;
	bool isStandby;
	bool isPut;
	bool isStart;
	bool isNext;
	float moveTimer;//��R�}�̃^�C�}�[
	float checkTime;//�R�}�̋�؂�
	int angleNum;
	std::vector<float> angles;
	std::vector<Vec2> anglesB;

};
#endif // !__PLAYER_ROBOT_H__
