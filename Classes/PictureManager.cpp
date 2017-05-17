#include "PictureManager.h"
#include "AllTags.h"

using namespace cocos2d;

PictureManager* PictureManager::create()
{
	PictureManager *pRet = new PictureManager();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool PictureManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	_LINE_MAX = _stageNum * 0.5f;

	// �^�b�`���ꂽ���Ƃ��擾����I�u�W�F�N�g
	auto listener = EventListenerTouchOneByOne::create();
	// �Ώۂ̃C�x���g�����s���ꂽ��A���ʂ̃C�x���g�͔�������Ȃ�����
	listener->setSwallowTouches(true);
	// �^�b�`���ꂽ�u�ԂɌĂ΂�郁�\�b�h��o�^
	listener->onTouchBegan = CC_CALLBACK_2(PictureManager::onTouchBegan, this);
	// �^�b�`����Ă���ԌĂ΂�郁�\�b�h��o�^
	listener->onTouchMoved = CC_CALLBACK_2(PictureManager::onTouchMoved, this);
	// �^�b�`�������ꂽ�u�ԂɌĂ΂�郁�\�b�h��o�^
	listener->onTouchEnded = CC_CALLBACK_2(PictureManager::onTouchEnded, this);
	// �C�x���g�̎��s�̗D�揇�ʂ��m�[�h�̏d�Ȃ菇�Ɉˑ�������
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	_bezierPos[0] = Vec2(0, -designResolutionSize.height*0.1f);
	_bezierPos[1] = Vec2(designResolutionSize.width*0.5f, -designResolutionSize.height*0.2f);
	_bezierPos[2] = Vec2(designResolutionSize.width, -designResolutionSize.height*0.1f);

	// �x�W�F�Ȑ�������
	float f = 0.0f;
	Vec2 vec, vec1;
	Vec2 basePos = Vec2(0,0);
	DrawNode *node = DrawNode::create();
	if (_stageNum <= _LINE_MAX)
	{
		basePos.y = designResolutionSize.height*0.75f;
		drawBezier(node, 50, basePos+_bezierPos[0], basePos + _bezierPos[1], basePos + _bezierPos[2]);
		/*v1 = Vec2(0, designResolutionSize.height*0.5f);
		v2 = Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.2f);
		v3 = Vec2(designResolutionSize.width, designResolutionSize.height*0.5f);*/
	}
	else
	{
		basePos.y = designResolutionSize.height;
		drawBezier(node, 50, basePos + _bezierPos[0], basePos + _bezierPos[1], basePos + _bezierPos[2]);
		basePos.y = designResolutionSize.height*0.5f;
		drawBezier(node, 50, basePos + _bezierPos[0], basePos + _bezierPos[1], basePos + _bezierPos[2]);
	}
	this->addChild(node);


	// �X�e�[�W�摜�\��
	if (_stageNum <= _LINE_MAX)
	{
		basePos.y = designResolutionSize.height*0.75f;
		for (int i = 0; i < _stageNum; i++)
		{
			_pictures[i] = Picture::create(i);
			float p = 1.0f / (_stageNum + 1);
			Vec2 b = bezier(p*(i + 1), basePos + _bezierPos[0], basePos + _bezierPos[1], basePos + _bezierPos[2]);
			b.y -= _pictures[i]->getContentSize().width / 2;
			_pictures[i]->setPosition(b);
			this->addChild(_pictures[i]);
		}
	}
	else
	{
		basePos.y = designResolutionSize.height;
		for (int i = 0; i < _LINE_MAX; i++)
		{
			_pictures[i] = Picture::create(i);
			float p = 1.0f / (_LINE_MAX + 1);
			Vec2 b = bezier(p*(i + 1), basePos + _bezierPos[0], basePos + _bezierPos[1], basePos + _bezierPos[2]);
			b.y -= _pictures[i]->getContentSize().width / 2;
			_pictures[i]->setPosition(b);
			this->addChild(_pictures[i]);
		}
		basePos.y = designResolutionSize.height*0.5f;
		for (int i = _LINE_MAX; i < _stageNum; i++)
		{
			_pictures[i] = Picture::create(i);
			float p = 1.0f / (_stageNum - _LINE_MAX + 1);
			Vec2 b = bezier(p*(i - _LINE_MAX + 1), basePos + _bezierPos[0], basePos + _bezierPos[1], basePos + _bezierPos[2]);
			b.y -= _pictures[i]->getContentSize().width / 2;
			_pictures[i]->setPosition(b);
			this->addChild(_pictures[i]);
		}
	}
	
	
	return true;
}

bool PictureManager::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	for (int i = 0; i < _stageNum; i++)
	{
		Rect rect = _pictures[i]->getBoundingBox();
		if (rect.containsPoint(pTouch->getLocation()))
		{
			_selectStage = i;
			_pictures[i]->setColor(Color3B::GRAY);
			_pictures[i]->setScale(1.2f);
			return true;
		}
	}
	return false;
}

void PictureManager::onTouchMoved(Touch* pTouch, Event* pEvent)
{

}

void PictureManager::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
	_pictures[_selectStage]->setColor(Color3B::WHITE);
	_pictures[_selectStage]->setScale(1.0f);
}

void PictureManager::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	_pictures[_selectStage]->setColor(Color3B::WHITE);
	Rect rect = _pictures[_selectStage]->getBoundingBox();
	if (rect.containsPoint(pTouch->getLocation()))
	{
		_pictures[_selectStage]->setColor(Color3B::WHITE);
		_pictures[_selectStage]->setScale(1.0f);
		log("ID = %d", _pictures[_selectStage]->_stageID);
	}
	else
	{
		_pictures[_selectStage]->setColor(Color3B::WHITE);
		_pictures[_selectStage]->setScale(1.0f);
	}
}

Vec2 PictureManager::bezier(float per, Vec2 pos0, Vec2 pos1, Vec2 po2)
{
	pos0.x = (1 - per)*(1 - per)*pos0.x + 2 * (1 - per)*per*pos1.x + per*per*po2.x;
	pos0.y = (1 - per)*(1 - per)*pos0.y + 2 * (1 - per)*per*pos1.y + per*per*po2.y;
	return pos0;
}

void PictureManager::drawBezier(DrawNode* dn, int seg, Vec2 pos0, Vec2 pos1, Vec2 pos2)
{
	float per = 0.0f;
	float f = 1.0f / seg;
	Vec2 vec0, vec1;
	for (int i = 0; i <= seg; i++)
	{
		vec0 = bezier(per, pos0, pos1, pos2);
		per = f*i;
		vec1 = bezier(per, pos0, pos1, pos2);
		dn->drawSegment(vec0, vec1, 1, Color4F::WHITE);
	}
}