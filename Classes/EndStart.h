#ifndef _EndStart_h_
#define _EndStart_h_

#include "cocos2d.h"
#include "CharacterAnimation.h"

class EndStart : public cocos2d::Layer
{
public:
	bool init();
	CREATE_FUNC(EndStart);

	cocos2d::Sprite* _upSp;
	cocos2d::Sprite* _downSp;

	cocos2d::Sprite* _charShadow[5];
	CharacterAnimation* _charAnim[5];
	CharacterAnimation* _char;
};

#endif // !_EndStart_h_
#pragma once
