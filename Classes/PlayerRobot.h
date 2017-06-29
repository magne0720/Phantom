#ifndef __PLAYER_ROBOT_H__
#define __PLAYER_ROBOT_H__

#include "cocos2d.h"
#include "Character.h"
#include "CutParticle.h"

#define MODE 0

USING_NS_CC;

//なぞった方向に移動をする
//
class PlayerRobot :public Character 
{
public:
	static PlayerRobot* create(Vec2 pos,Color4F col=Color4F(0,0,0,0));
	bool init(Vec2 pos,Color4F col);

	void plusAction();

	//角度の保存
	void setAngle(Vec2 from, Vec2 to);
	//歩き始める
	void moveStartPosition();
	//つぎに行くべきところの設定
	void nextPosition();
	//次に行く場所がなくなった時に配列の中を削除し、動きを止める
	void stopPosition();
	//ゴールした時
	void findPosition();

	//止まった時のアニメーション
	void stopAnimation();
	//ゴールした時のアニメーション
	void findAnimation();


	//プレイヤーの操作が異なるので仮想化
	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);

	//
	//設定時のスタート位置
	Vec2 startPosition;
	//一定区間超えた位置
	Vec2 endPosition;
	//移動準備しているか
	bool isStandby;
	//動き始めたか
	bool isStart;
	//動いているか
	bool isMove;

	float moveTimer;//一コマのタイマー
	float checkTime;//コマの区切り
	int angleNum;
	std::vector<float> angles;
	Sprite* messageSp;
	CutParticle* goalPa;

};
#endif // !__PLAYER_ROBOT_H__
