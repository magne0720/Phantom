#ifndef __WALL_H__
#define __WALL_H__

#include "cocos2d.h"
#include "AllTags.h"
USING_NS_CC;

//線に挟まれたときに面積の少ないほうが消滅する壁
class Wall :public Node 
{
public:
	Wall() {};
	static Wall* create(Vec2 spawnPos);
	bool init(Vec2 spawnPos);

	Sprite* mySprite;
	Vec2 myPosition;
	SEGMENT segments[6];

	//新しくポイントを設定する
	void setPoint(int number, Vec2 point);
	//from-to間の線とtargetの交点を調べる
	int checkPoint(Vec2* hitPos,SEGMENT s0,SEGMENT s1);
	//切り取られる演出
	void cutEffect();
	//当たり判定
	bool onCollision(Vec2 start, Vec2 end);

};

#endif // !__WALL_H__
