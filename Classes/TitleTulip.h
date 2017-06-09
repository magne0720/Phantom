#ifndef _TitleTulip_h_
#define _TitleTulip_h_

#include "cocos2d.h"

class TitleTulip : public cocos2d::Node
{
public:
	bool init();
	static TitleTulip* create();

	const int TULIP_NUM = 10;
	cocos2d::Sprite* _tulip[10];
	void update(float delta);
};

#endif // !_TitleTulip_h_