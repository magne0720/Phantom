#ifndef _TitleLogo_h_
#define _TitleLogo_h_

#include "cocos2d.h"

class TitleLogo : public cocos2d::Node
{
public:
	bool init();
	static TitleLogo* create();
private:
	cocos2d::Sprite* _logoSp;
	cocos2d::Sprite* _shadowSp;
};

#endif // !_TitleLogo_h_
