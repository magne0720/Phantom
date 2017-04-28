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
	float doubtRange;

	float thinkTimer;


public:
	static Enemy* create(Vec2 spawnPos,DIR_DEGREE dir=DIR_DEGREE::DIR_DOWN);
	virtual bool init(Vec2 spawnPos,DIR_DEGREE dir);
	virtual void update(float delta);

	virtual void action();
	
	//主人公たちがいないか確かめる
	bool checkPlayer(Vec2 playerPos);
	//視認距離の変更
	void changeRange(float range);
	//視認範囲の変更
	void changeDegree(float degree);
	//思考フェイズ
	void moveThink(float time);


};

#endif // !__ENEMY_H__
