#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "Character.h"

USING_NS_CC;

//敵の基本思考
class Enemy :public Character 
{
private:

	//プレイヤー確認範囲
	float doubtRange,doubtDegree;
	STATUS myState;

public:
	static Enemy* create(Vec2 spawnPos);
	virtual bool init(Vec2 spawnPos);

	virtual void action();
	
	bool checkPlayer(Vec2 playerPos);
	bool checkPlayerRight(float Range);
	bool checkPlayerLeft(float Range);
	void setState(STATUS state);


};

#endif // !__ENEMY_H__
