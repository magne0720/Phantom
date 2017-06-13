#ifndef _Batterfly_h_
#define _Batterfly_h_

#include "cocos2d.h"
#include "ColorEnum.h"

class Batterfly : public cocos2d::Sprite
{
public:
	bool init(bool purple, bool blue);
	static Batterfly* create(bool purple = false, bool blue = false);
	void update(float delta);
	float scaleRange(float f);

	eColor _colors[2] = { eColor::PURPLE, eColor::BLUE };
	bool _bPurple, _bBlue;
	cocos2d::Sprite* _mySp;
	float _scaling;
};

#endif // !_Batterfly_h_
