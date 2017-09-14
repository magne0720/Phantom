#ifndef _EndTitle_h_
#define _EndTitle_h_

#include "cocos2d.h"

class EndTitle : public cocos2d::Layer
{
public:
	bool init();
	CREATE_FUNC(EndTitle);

	void update(float delta);

	//cocos2d::Sprite* _stuffSp[6];
private:
	cocos2d::Sprite* _map;

	float _timer = 0.0f;
	const float _STOP_TIME = 3.0f;
	const float _MOVE_TIME = 5.0f;
	bool _isStopped = false;
	int cnt = 0;
	const int _COUNT = 7;
};

#endif // !_EndTitle_h_
