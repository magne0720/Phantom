#ifndef __MAP_CREATOR_H__
#define __MAP_CREATOR_H__

#include "cocos2d.h"
#include "PlayerPhantom.h"
#include "Enemy.h"
#include "Wall.h"

#include <iostream>

//読み込みの長さ指定
//DATA_LENGTH_PLAYERのような感じ
#define D_L_PLAYER 16
#define D_L_ENEMY 10
#define D_L_WALL 0


using namespace std;

USING_NS_CC;

class MapCreator:public Node
{
private:

	//キャラクター
	//void createPlayer(float x, float y);

public:

	static MapCreator* create();
	bool init();

	//マップ情報
	Vector<String*> names;
	Vector<Character*> characters;
	Vector<Wall*> walls;
	Vector<Node*> floors;


	//マップファイル読み込み
	void openMapFile(char* name);
	//マップ情報管理関数
	void loadMap(string mapText);
	//マップ情報の追加
	void pushObject(Character*& obj,String*& id);
	//マップ情報の追加
	void pushObject(Wall*& obj, String*& id);
	//マップ情報の追加
	void pushObject(Node*& obj, String*& id);
	//マップの配置
	void putObject(Character* &obj, Vec2 pos);
	//配置キャラの解析
	void analyzePlayer(char* data);
	void analyzeEnemy(char* data);
	void analyzeWall(char* data);
	void analyzeObject(char* data);
	char* getAnalyzeData(string text,int offset,int length);



};


#endif // !__MAP_CREATOR_H__
