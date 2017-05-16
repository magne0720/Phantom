#ifndef __PLAYER_DOG_H__
#define __PLAYER_DOG_H__

#include "cocos2d.h"
#include "Character.h"

USING_NS_CC;

//�X���C�v�����ʒu�Ɉړ����錢�N���X
class PlayerDog : public Character 
{
private:
	float rangeTimer;
	float rangeSpeed;
public:
	static PlayerDog* create(Vec2 spawnPos,  DIR_DEGREE dir = DIR_DEGREE::DIR_DOWN);
	bool init(Vec2 spawnPos, DIR_DEGREE dir = DIR_DEGREE::DIR_DOWN);
	//�ړ��\����
	bool canMoveRange(Point target,float range);

	//�����ړ��͈͐ݒ�
	void setMoveStartRange(float range);
	//�ړ��͈͊g�呬�x�ݒ�
	void setRangeSpeed(float range);

	void plusAction();


	//�^�b�v���Ĉړ��ҋ@���邩�̔��蔼�a
	float moveStartRange;

	bool onTouchBegan(const Touch * touch, Event *unused_event);
	void onTouchMoved(const Touch * touch, Event *unused_event);
	void onTouchEnded(const Touch * touch, Event *unused_event);


};

#endif // !__PLAYER_DOG_H__
