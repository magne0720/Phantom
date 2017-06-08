#ifndef _PictureManager_
#define _PictureManager_

#include "cocos2d.h"
#include "Picture.h"
#include <vector>

class PictureManager : public cocos2d::Node
{
public:
	static PictureManager* create();
	bool init();
	void update(float delta);

	// タッチイベント処理
	bool onTouchBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
	void onTouchCancelled(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
	void onTouchEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);

	bool onTouchBeganP(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
	void onTouchCancelledP(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
	void onTouchEndedP(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event);
	
private:
	Picture* _pictures[10];
	float _touchTimer;
	const float _TOUCH_REACTION = 0.4f;
	int _stageNum = 10;	// 現在のステージ数
	int _LINE_MAX = 5;	//　1ラインに入る枚数
	cocos2d::Vec2 _bezierPos[3];	// 基準点とベジェ曲線の為に必要な3点の差
	int _selectedStage = 0;	// 現在選択されているステージ
	bool _areResizing;	// リサイズ中であるか
	int _touchID;		// 現在判定しているタッチのID

	cocos2d::EventListenerTouchAllAtOnce* listener;

	cocos2d::Vec2 bezier(float per, cocos2d::Vec2 pos0, cocos2d::Vec2 pos1, cocos2d::Vec2 po2);
	void drawBezier(cocos2d::DrawNode* dn, int seg, cocos2d::Vec2 pos0, cocos2d::Vec2 pos1, cocos2d::Vec2 pos2);
	
	void defaultSize();
	void selectedSize();
	void popedUpSize();
	void selectedInit();
	void touchIDInit();

	enum class eTOUCH
	{
		BEGAN,
		MOVED,
		ENDED,
		CANCELLED
	};

	void changeBool(bool (PictureManager::*method)(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event));
	void changeVoid(void (PictureManager::*method)(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event), eTOUCH eTouch);

	struct PicSize
	{
		float scale;
		cocos2d::Vec2 position;
		int z;
	};

	PicSize _defaultPic;
	PicSize _popedUpPic;
	float _per;
	float _add;

	void swap(float &a, float &b);
	void swap(int &a, int &b);
	void swap(cocos2d::Vec2 &a, cocos2d::Vec2 &b);

	cocos2d::Label* label;
};

#endif
