#ifndef _TitleWood_h_
#define _TitleWood_h_

#include "cocos2d.h"
#include "Wood.h"
#include "ScrollSprite.h"

class TitleWood : public cocos2d::Node
{
public:
	bool init();
	static TitleWood* create();
	
	Wood* _wood[4];

};
#endif // !_TitleWood_h_
