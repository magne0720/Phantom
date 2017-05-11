#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "Character.h"

USING_NS_CC;

//�G�̊�{�v�l
class Enemy :public Character 
{
private:
	//�v���C���[�m�F�͈�
	float doubtRange;

	float thinkTimer;


public:
	static Enemy* create(Vec2 spawnPos,DIR_DEGREE dir=DIR_DEGREE::DIR_DOWN);
	virtual bool init(Vec2 spawnPos,DIR_DEGREE dir);
	void plusAction();
	
	//��l�����������Ȃ����m���߂�
	bool checkPlayer(Vec2 playerPos);
	//���F�����̕ύX
	void changeRange(float range);
	//���F�͈͂̕ύX
	void changeDegree(float degree);
	//�v�l�t�F�C�Y
	void moveThink(float time);
	//�Փ˔���܂Ƃ�
	void allCollision();

};

#endif // !__ENEMY_H__
