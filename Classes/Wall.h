#ifndef __WALL_H__
#define __WALL_H__

#include "cocos2d.h"
#include "AllTags.h"
USING_NS_CC;

//���ɋ��܂ꂽ�Ƃ��ɖʐς̏��Ȃ��ق������ł����
class Wall :public Node 
{
public:
	Wall() {};
	static Wall* create(Vec2 spawnPos);
	bool init(Vec2 spawnPos);

	Sprite* mySprite;
	Vec2 myPosition;
	SEGMENT segments[6];

	//�V�����|�C���g��ݒ肷��
	void setPoint(int number, Vec2 point);
	//from-to�Ԃ̐���target�̌�_�𒲂ׂ�
	int checkPoint(Vec2* hitPos,SEGMENT s0,SEGMENT s1);
	//�؂����鉉�o
	void cutEffect();
	//�����蔻��
	bool onCollision(Vec2 start, Vec2 end);

};

#endif // !__WALL_H__
