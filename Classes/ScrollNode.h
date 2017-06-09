#ifndef _ScrollNode_h_
#define _ScrollNode_h_

#include "cocos2d.h"
#include <vector>

class ScrollNode : public cocos2d::Node
{
public:
	enum eOrientation
	{
		landscape,	// ��
		portrait	// �c
	};

	static ScrollNode* create(float scrollSpeed, eOrientation orientation = landscape);
	
	bool init(float scrollSpeed, eOrientation orientation);
	//void update(float delta);
	void updateL(float delta);
	void updateP(float delta);
	void setScrollNodeSpeed(float speed);	// �X�N���[���X�s�[�h�ύX

	static std::vector<cocos2d::Node*> _bgNodes;
	float _scrollSpeed;
};

#endif