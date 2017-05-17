#ifndef _Picure_h_
#define _Picure_h_

#include "cocos2d.h"

class Picture : public cocos2d::Sprite
{
public:
	cocos2d::Sprite* _shadow;
	cocos2d::Sprite* _clip;
	int _stageID;

	bool init(int id);
	static Picture* create(int id);
};

#endif