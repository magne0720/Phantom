#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
#include "MapCreator.h"
#include "TitleSelectScene.h"
#include "SaveData.h"

USING_NS_CC;

class GameManager :public Node 
{
public:

	static GameManager* create(int num);
	bool init(int num);
	void update(float delta);

	bool standbyAnimation();
	bool startAnimation();
	bool stopAnimation();
	bool missAnimation();

	void StayShowMessage(int num);
	void StayCloseMessage();


	void dispLife(int life,int max);
	void dispGoal();
	void checkTime();



	SaveData* user;
	MapCreator* map;
	bool* isGoal;
	bool isGoalAnimation; 
	bool isTouched;
	Color4F stageColor;
	GAMESTATE gameState;
	Sprite* messageSp;
	Vector<Sprite*> lifeSps;
	int playerLife,maxLife;

	int playerCount;//プレイヤーの行動可能回数

	float timer;


	//プレイヤーの操作が異なるので仮想化
	virtual bool onTouchBegan(const Touch * touch, Event *unused_event);
	virtual void onTouchMoved(const Touch * touch, Event *unused_event);
	virtual void onTouchEnded(const Touch * touch, Event *unused_event);


};


#endif // !__GAME_MANAGER_H__
