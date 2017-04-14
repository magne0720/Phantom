#ifndef __PLAYER_DOG_H__
#define __PLAYER_DOG_H__

#include "cocos2d.h"
#include "Character.h"

USING_NS_CC;

//�X���C�v�����ʒu�Ɉړ����錢�N���X
class PlayerDog : public Character 
{
public:
	static PlayerDog* create(Vec2 spawnPos);
	bool init(Vec2 spawnPos);
	//�ړ��\����
	bool canMoveRange(Point target,float range);

	//�^�b�v���n�߂Ĉړ��\�͈͂������~��
	DrawNode* moveStartRangeSp;
	//�^�b�v���Ĉړ��ҋ@���邩�̔��蔼�a
	float moveStartRange;

	bool onTouchBegan(const Touch * touch, Event *unused_event);
	void onTouchMoved(const Touch * touch, Event *unused_event);
	void onTouchEnded(const Touch * touch, Event *unused_event);


};

#endif // !__PLAYER_DOG_H__
