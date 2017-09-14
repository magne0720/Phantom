#ifndef __WARPHOLE_H__
#define __WARPHOLE_H__

#include "AllTags.h"
#include "ObjectBase.h"

using namespace std;

class WarpHole :public ObjectBase 
{
public:
	static WarpHole* create(Vec2 spawnPos);
	//�����ݒ�
	virtual bool init(Vec2 spawnPos);
	//�X�V
	virtual void update(float delta);

	Vec2 myPosition;
	Vec2 partnerPosition;
	WarpHole* partner;
	bool isHit;
	float collider;
	float timer;
	vector<int> hits;
	Sprite* mySprite;

	//�Ώۂ����g�ɏՓ˂����炻�̑Ώۂ��u�Ԉړ�������
	//�����葱���Ă���ꍇ�͖����ɂȂ�
	void objectWarp(Vec2& target, Vec2& partner);




};


#endif // !__WARPHOLE_H__
