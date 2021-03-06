#ifndef __WARPHOLE_H__
#define __WARPHOLE_H__

#include "AllTags.h"
#include "ObjectBase.h"

using namespace std;

class WarpHole :public ObjectBase 
{
public:
	static WarpHole* create(Vec2 spawnPos);
	//初期設定
	virtual bool init(Vec2 spawnPos);
	//更新
	virtual void update(float delta);

	Vec2 myPosition;
	Vec2 partnerPosition;
	WarpHole* partner;
	bool isHit;
	float collider;
	float timer;
	vector<int> hits;
	Sprite* mySprite;

	//対象が自身に衝突したらその対象を瞬間移動させる
	//当たり続けている場合は無効になる
	void objectWarp(Vec2& target, Vec2& partner);




};


#endif // !__WARPHOLE_H__
