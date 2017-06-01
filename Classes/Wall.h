#ifndef __WALL_H__
#define __WALL_H__

#include "cocos2d.h"
#include "AllTags.h"
USING_NS_CC;

//線に挟まれたときに面積の少ないほうが消滅する壁
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

	//判定を取る線
	Vec2 *fromPos,*toPos;

	//------------------------------------------
	//次はこれを使って分割処理をする
	//追加した位置の番号
	int addPointNum[2];
	//-----------------------------------------

	void setTargets(Vec2* from,Vec2* to);
	//新しくポイントを設定する
	void setPoint(int number, Vec2 point);
	//衝突判定命令
	void callCollision();
	//from-to間の線とtargetの交点を調べる
	int checkPoint(Vec2* hitPos, SEGMENT s0, SEGMENT s1);
	//検出した点がどの線に所属しているかを調べ、その線を境に分割する
	void cutSegment(Vec2* hitPos, SEGMENT& from, SEGMENT& out);
	//配列の中を先頭から3つずつ取り出した点で面積の合計を返す
	float sumArea(int point[]);
	//角の頂点をなくして、その頂点をつないでいた線同士をつないだ5角形を作る
	void changePentagon(int pointNum);
	//切り取る場所検出
	void checkCutArea();
	//切り取った後に面積を再構築する視覚効果
	void rebuildingArea(int corner);

	//切り取られる演出
	void cutEffect();
	//当たり判定
	bool onCollision(Vec2 start, Vec2 end);
	//間にある点をセグメントとして使う配列のソート(取り出す番地,ほしい配列番地)
	void sortSegment(int pic,int target,int addNum=-1);
	//セグメント入れ替え
	void swapSegment(int one, int two);
};

#endif // !__WALL_H__
