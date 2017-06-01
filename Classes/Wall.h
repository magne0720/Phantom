#ifndef __WALL_H__
#define __WALL_H__

#include "cocos2d.h"
#include "AllTags.h"
USING_NS_CC;

//���ɋ��܂ꂽ�Ƃ��ɖʐς̏��Ȃ��ق������ł����
class Wall :public Node
{
public:
	static Wall* create(Vec2 spawnPos);
	bool init(Vec2 spawnPos);
	void update(float delta);

	float cutTimer;
	Sprite* mySprite;
	Vec2 myPosition;
	SEGMENT segments[6];
	bool isCuted;
	DrawNode* myWall;
	ClippingNode* clipp;

	//���������
	Vec2 *fromPos,*toPos;

	//------------------------------------------
	//���͂�����g���ĕ�������������
	//�ǉ������ʒu�̔ԍ�
	int addPointNum[2];
	//-----------------------------------------

	void setTargets(Vec2* from,Vec2* to);
	//�V�����|�C���g��ݒ肷��
	void setPoint(int number, Vec2 point);
	//�Փ˔��薽��
	void callCollision();
	//from-to�Ԃ̐���target�̌�_�𒲂ׂ�
	int checkPoint(Vec2* hitPos, SEGMENT s0, SEGMENT s1);
	//���o�����_���ǂ̐��ɏ������Ă��邩�𒲂ׁA���̐������ɕ�������
	void cutSegment(Vec2* hitPos, SEGMENT& from, SEGMENT& out);
	//�z��̒���擪����3�����o�����_�Ŗʐς̍��v��Ԃ�
	float sumArea(int point[]);
	//�p�̒��_���Ȃ����āA���̒��_���Ȃ��ł��������m���Ȃ���5�p�`�����
	void changePentagon(int pointNum);
	//�؂���ꏊ���o
	void checkCutArea();
	//�؂�������ɖʐς��č\�z���鎋�o����
	void rebuildingArea(int corner);

	//�؂����鉉�o
	void cutEffect();
	//�����蔻��
	bool onCollision(Vec2 start, Vec2 end);
	//�Ԃɂ���_���Z�O�����g�Ƃ��Ďg���z��̃\�[�g(���o���Ԓn,�ق����z��Ԓn)
	void sortSegment(int pic,int target,int addNum=-1);
	//�Z�O�����g����ւ�
	void swapSegment(int one, int two);
};

#endif // !__WALL_H__
