#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "AllTags.h"
#include "Wall.h"

USING_NS_CC;


//キャラクターの基底クラス。
//移動、衝突判定、移動速度などの基本情報
class Character:public Node
{
public:
	static Character* create(Vec2 spawnPos);
	//初期画像を中心に配置
	void initWithFileCenter(std::string name);
	//初期設定
	virtual bool init(Vec2 spawnPos);
	//更新
	virtual void update(float delta);
	//初期設定
	void initialize(Vec2 pos);



	
	//更新処理
	//-----------------------------------------
	//キャラクターの基本行動
	void action();
	//追加行動
	virtual void plusAction();
	//移動
	virtual void move(float plusSpeed=1.0f);
	//-----------------------------------------

	//判定処理
	//-----------------------------------------
	//今lastTargetPositionにいるか
	bool onLastTargetPosition(Vec2 pos);
	//ターゲット範囲に入っているか
	virtual bool onCollision(Vec2 pos,float range);
	//自身と引数(相手)の円判定
	virtual bool onCollision(Character* p);
	//赤外線判定
	virtual bool onCollision(Vec2 start, Vec2 end);
	//移動可能判定
	bool onMoveRange(Point target);
	//右側にあるか
	bool onDirectionRight(const Vec2 target);
	//左側にあるか
	bool onDirectionLeft(const Vec2 target);
	//進む方向が壁かどうか
	bool onWall(Vector<Wall*> quad);
	//衝突判定まとめ
	virtual void allCollision();
	//-----------------------------------------


	//ゲッター
	//-----------------------------------------

	//方向ベクトルから指定角度で自身の視認範囲のベクトルを取得する
	Vec2 getDirectionDegree(Vec2 target, float deg, float range = 1.0f);
	//向きの取得
	Vec2 getDirectionVector();
	//-----------------------------------------


	//セッター
	//-----------------------------------------
	//状態変化
	void setState(STATUS state);
	//当たり判定のあるものを設定
	void setTarget(Character* p);
	//当たり判定のあるものを設定
	void setTarget(Wall* p);
	//速度の変更
	void setSpeed(float speed);
	//移動可能範囲変更
	void setMoveRange(float range);
	//視認範囲設定
	void setDoubtDgree(float range);
	//移動場所設定
	void setTargetPosition(Vec2 pos);
	//360度の向き変更
	void setDirection(float degree);
	//向きによってもらうベクトルと進む方向でどちらの方向に回転するかを決める
	void setEvasionWall(Vec2 wall, Vec2 target);
	//-----------------------------------------

	
	//計算処理
	//-----------------------------------------
	//正規化
	Vec2 normalize(Vec2 pos);
	//内積
	float dot(Vec2 from, Vec2 to);
	//長さ
	float length(Vec2 pos);
	//-----------------------------------------


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
	//予定された最終場所。ここにつくまで移動する。
	Vec2 lastTargetPosition;

	//自身の向き
	float myDirection;
	//移動速度
	float moveSpeed;
	//移動可能範囲半径
	float moveRange;
	//視認範囲
	float doubtDegree;
	//自身と当たり判定のある物
	Vector<Character*> targets;
	//壁
	Vector<Wall*> walls;
	//自身の状態
	STATUS myState;




	//プレイヤーの操作が異なるので仮想化
	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);

};

#endif // !__CHARACTER_H__
