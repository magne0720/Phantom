#ifndef __PLAYER_ROBOT_H__
#define __PLAYER_ROBOT_H__

#include "cocos2d.h"
#include "Character.h"
#include "CutParticle.h"

#define MODE 0

USING_NS_CC;

//�Ȃ����������Ɉړ�������
//
class PlayerRobot :public Character 
{
public:
	static PlayerRobot* create(Vec2 pos,Color4F col=Color4F(0,0,0,0));
	bool init(Vec2 pos,Color4F col);

	void plusAction();

	//�p�x�̕ۑ�
	void setAngle(Vec2 from, Vec2 to);
	//�����n�߂�
	void moveStartPosition();
	//���ɍs���ׂ��Ƃ���̐ݒ�
	void nextPosition();
	//���ɍs���ꏊ���Ȃ��Ȃ������ɔz��̒����폜���A�������~�߂�
	void stopPosition();
	//�S�[��������
	void findPosition();

	//�~�܂������̃A�j���[�V����
	void stopAnimation();
	//�S�[���������̃A�j���[�V����
	void findAnimation();


	//�v���C���[�̑��삪�قȂ�̂ŉ��z��
	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);

	//
	//�ݒ莞�̃X�^�[�g�ʒu
	Vec2 startPosition;
	//����Ԓ������ʒu
	Vec2 endPosition;
	//�ړ��������Ă��邩
	bool isStandby;
	//�����n�߂���
	bool isStart;
	//�����Ă��邩
	bool isMove;

	float moveTimer;//��R�}�̃^�C�}�[
	float checkTime;//�R�}�̋�؂�
	int angleNum;
	std::vector<float> angles;
	Sprite* messageSp;
	CutParticle* goalPa;

};
#endif // !__PLAYER_ROBOT_H__
