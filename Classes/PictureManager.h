#ifndef _PictureManager_
#define _PictureManager_

#include "cocos2d.h"
#include "Picture.h"

class PictureManager : public cocos2d::Node
{
public:
	static PictureManager* create();
	bool init();

	// タッチイベント処理
	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	
private:
	Picture* _pictures[10];
	int _stageNum = 10;	// 現在のステージ数
	int _LINE_MAX = 5;	//　1ラインに入る枚数
	cocos2d::Vec2 _bezierPos[3];	// 基準点とベジェ曲線の為に必要な3点の差
	int _selectStage = 0;	// 現在選択されているステージ

	cocos2d::Vec2 bezier(float per, cocos2d::Vec2 pos0, cocos2d::Vec2 pos1, cocos2d::Vec2 po2);
	void drawBezier(cocos2d::DrawNode* dn, int seg, cocos2d::Vec2 pos0, cocos2d::Vec2 pos1, cocos2d::Vec2 pos2);
};

#endif
