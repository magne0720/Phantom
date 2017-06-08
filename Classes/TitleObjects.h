#ifndef _TitleObjects_h_
#define _TitleObjects_h_

#include "cocos2d.h"

class TitleObjects : public cocos2d::Node
{
public:
	bool init();
	static TitleObjects* create();
};

#endif // !_TitleObjects_h_
