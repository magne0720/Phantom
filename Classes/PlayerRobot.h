#ifndef __PLAYER_ROBOT_H__
#define __PLAYER_ROBOT_H__

#include "cocos2d.h"
#include "Character.h"

#define MODE 0

USING_NS_CC;

//なぞった方向に移動をする
//
class PlayerRobot :public Character 
{
public:
	static PlayerRobot* create(Vec2 pos);
	bool init(Vec2 pos);

	void plusAction();

	//角度の保存
	void setAngle(Vec2 from, Vec2 to);
	//つぎに行くべきところの設定
	void nextPosition();
	//次に行く場所がなくなった時に配列の中を削除し、動きを止める
	void stopPosition();
	//絶対操作
	void nextPositionB();
	void stopPositionB();

	//プレイヤーの操作が異なるので仮想化
	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);


	//設定時のスタート位置
	Vec2 startPosition;
	//一定区間超えた位置
	Vec2 endPosition;
	//
	Vec2 touchPosition;
	bool isStandby;
	bool isPut;
	bool isStart;
	bool isNext;
	float moveTimer;//一コマのタイマー
	float checkTime;//コマの区切り
	int angleNum;
	std::vector<float> angles;
	std::vector<Vec2> anglesB;

};
#endif // !__PLAYER_ROBOT_H__
