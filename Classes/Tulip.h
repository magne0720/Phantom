#ifndef _Tulip_h_
#define _Tulip_h_

#include "cocos2d.h"

class Tulip : public cocos2d::Sprite
{
public:
	bool init();
	static Tulip* create();
};
#endif // !_Tulip_h_
