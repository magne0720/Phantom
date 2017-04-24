#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "AllTags.h"

USING_NS_CC;


//キャラクターの基底クラス。
//移動、衝突判定、移動速度などの基本情報
class Character:public Node
{
public:
	static Character* create(Vec2 spawnPos);
	void initWithFileCenter(std::string name);
	//初期設定
	virtual bool init(Vec2 spawnPos);
	//更新
	virtual void update(float delta);
	//移動可能判定
	bool canMoveRange(Point target);
	//各キャラクターの行動
	virtual void action();
	//移動
	virtual void move();
	//衝突判定
	virtual bool onCollision(float deg);
	//赤外線判定
	virtual bool onCollision(Vec2 start, Vec2 end);
	//速度の変更
	void setSpeed(float speed);
	//移動可能範囲変更
	void setMoveRange(float range);
	//方向変更
	void setDirection(float seta,float alpha=1.0f);
	//方向取得
	Vec2 getDirectionVector(Vec2 target,float range=1.0f);
	//方向ベクトルから指定角度で自身の視認範囲のベクトルを取得する
	Vec2 getDirectionDegree(float deg, float range = 1.0f);
	//右側にあるか
	bool getDirectionRight(Vec2 target);
	//左側にあるか
	bool getDirectionLeft(Vec2 target);


	//移動待機状態かどうか
	bool isMoveWait;
	//移動可能範囲を示す円環
	DrawNode* moveRangeSp;
	//自身の画像
	Sprite* mySprite;
	//自身の場所
	Vec2 myPosition;
	//次に向かう場所。これに向かうために移動を行う。
	Vec2 targetPosition;
	//自身の向き
	DIR_DEGREE myDirection;
	//移動速度
	float moveSpeed;
	//移動可能範囲半径
	float moveRange;
	//視認範囲
	float doubtDegree;

	//プレイヤーの操作が異なるので仮想化
	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);

};

#endif // !__CHARACTER_H__
