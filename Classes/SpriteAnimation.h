#ifndef _SpriteAnimation_h_
#define _SpriteAnimation_h_

#include "cocos2d.h"

class SpriteAnimation : public cocos2d::Node
{
public:
	bool init(std::string fileName, int num);
	static SpriteAnimation* create(std::string fileName, int num);	// �t�@�C���l�[��, �X�v���C�g�K�v����
	
};

#endif // !_SpriteAnimation_h_
