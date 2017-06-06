#include "MapCreator.h"

MapCreator* MapCreator::create() 
{
	MapCreator *pRet = new MapCreator();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};
};

bool MapCreator::init() 
{
	if (!Node::init()) 
	{
		return false;
	}
//	log("openMapCreator");
	openMapFile("test");

	d = DrawNode::create();
	addChild(d, 500);

	scheduleUpdate();

	return true;
};

void MapCreator::update(float delta)
{
	if (robot->isRobotMoving) {
		for (int i = 0; i < walls.size();i++)
			walls.at(i)->callCollision();
	}
};

//マップファイル読み込み
void MapCreator::openMapFile(char* name)
{
	String* filename = String::createWithFormat("Stages/%s.bin", name);
	string fileText = FileUtils::getInstance()->getStringFromFile(filename->getCString());

	loadMap(fileText);
};

//マップ情報管理関数
void MapCreator::loadMap(string mapText) 
{
	for (int i = 0; mapText.size()>i; i++)//データが終わるまで
	{
		switch (mapText[i])
		{
		case 'C'://Character
			log("characterStart");
			analyzePlayer(getAnalyzeData(mapText.substr(i+2,i+D_L_PLAYER),D_L_PLAYER));
			log("characterEnd\n--------------------------------------");
			i += D_L_PLAYER;
			break;
		case 'E'://ENEMY
			log("enemyStart");
			analyzeEnemy(getAnalyzeData(mapText.substr(i + 1, i + D_L_ENEMY), D_L_ENEMY));
			i += D_L_ENEMY;
			log("enemyEnd\n--------------------------------------");
			break;
		case 'W'://Wall
			log("wallStart");
			analyzeWall(getAnalyzeData(mapText.substr(i + 1, i + D_L_WALL), D_L_WALL));
			i += D_L_WALL;
			log("wallEnd\n--------------------------------------");
			break;
		case 'F'://Floor
			log("floorStart");
			analyzeFloor(getAnalyzeData(mapText.substr(i + 1, mapText.size()-i),D_L_FLOOR));
			i += D_L_FLOOR;
			log("floorend\n--------------------------------------");
			break;
		default:
			//log("default");
			break;
		}
	}
};


void MapCreator::pushObject(Enemy*& obj, String* &id)
{
	names.pushBack(id);
	enemys.pushBack(obj);
};

void MapCreator::pushObject(Wall*& obj, String* &id)
{
	names.pushBack(id);
	walls.pushBack(obj);
};

void MapCreator::pushObject(Node*& obj, String* &id)
{
	names.pushBack(id);
	floors.pushBack(obj);
};

//マップの配置
void MapCreator::putObject(Character* &obj, Vec2 pos)
{

};

//配置キャラの解析
//主人公21,
//敵12
void MapCreator::analyzePlayer(char* data)
{
	Vec2 oneP, twoP;
	DIR_DEGREE oneR=DIR_DEGREE::DIR_DOWN, twoR=DIR_DEGREE::DIR_DOWN;

			oneP.x = getCharToFloat(data);
			//4バイト単位で座標を管理しているため
			data += 4;
			oneP.y = getCharToFloat(data);
			data += 4;
			twoP.x = getCharToFloat(data);
			data += 4;
			twoP.y = getCharToFloat(data);
	log("human[%f,%f]", oneP.x, oneP.y);
	log("dog[%f,%f]", twoP.x, twoP.y);

	robot = PlayerCloser ::create(oneP, twoP);
	log("push-player");

};
void MapCreator::analyzeEnemy(char* data)
{
	Vec2 pos;
	getCharToInt(data, 3);
	data += 3;
	DIR_DEGREE d=getCharToDirction(data);
	data += 1;
	pos.x = getCharToFloat(data);
	data += 4;
	pos.y = getCharToFloat(data);
	Enemy* e = Enemy::create(pos,d);
	enemys.pushBack(e);
	log("enemy[%f,%f]", pos.x, pos.y);
	log("push-enemy");
};
void MapCreator::analyzeWall(char* data)
{
	Vec2 pos;
	//壁の種類3byte

	//↑に入れる
	data += 3;
	pos.x = getCharToFloat(data);
	data += 4;
	pos.y = getCharToFloat(data);
	Wall* w = Wall::create(pos);
	walls.pushBack(w);
	log("wall[%f,%f]", pos.x, pos.y);
	log("push-wall");
};

void MapCreator::analyzeObject(char* data)
{

};

void MapCreator::analyzeFloor(char* data)
{
	int maxX = getCharToInt(data);
	data += 4;
	int maxY = getCharToInt(data);
	log("map=[%d%d]", maxX, maxY);

	//マップチップ取得
	SpriteBatchNode* batch = SpriteBatchNode::create("mapChip.png");
	addChild(batch);
	int chipNum = 3;

	char* mapData = analyzeData;
	//座標分のシフト
	mapData += D_FLOOR_LINE;

	for (int y = 0; y<maxY; y++)
		for (int x = 0; x<maxX; x++)
		{
			//二文字ずつ取得
			//64は画像サイズ。タイリングマップチップ
			Sprite* sp = Sprite::createWithTexture(batch->getTexture(),
				Rect(getHexToInt(mapData++)* TILE_SIZE, getHexToInt(mapData++)*TILE_SIZE,TILE_SIZE,TILE_SIZE),false);
			sp->setPosition(Vec2(chipNum*x*TILE_SIZE+(TILE_SIZE/2),(maxY*TILE_SIZE)-chipNum*y*TILE_SIZE+(TILE_SIZE/2)));
			sp->setScale(chipNum);
			floors.pushBack(sp);
		//	log("map[%d,%d]", x,y);
		}
};

char* MapCreator::getAnalyzeData(string text, int length)
{
	//必ず解析データを初期化する
	for (int i = 0; i < length;i++)
	{
		analyzeData[i] = '\0';
	}
	//なんか16バイトずつで読み込んでるtextくん

	for (int i = 0; i < length&&i<text.size(); i++) 
	{
		analyzeData[i] = text[i];
	};
	//log("%s", analyzeData);
	return analyzeData;
};

float MapCreator::getCharToFloat(char* data,int length) 
{
	if (length >= 16)
	{
		log("error!-sizeover-[16]<length");
		return 0;
	}

	char buf[16];
		for (int j = 0; j < length; j++)
		{
			buf[j] = *data;
			data++;
		}
		buf[length] = '\0';
		log("floatbuf-%s", buf);
		return (float)atof(buf);
};

int MapCreator::getCharToInt(char* data, int length) 
{
	if (length >= 16) 
	{
		log("error!-sizeover-[16]<length");
		return 0;
	}

	char buf[16];
	for (int i = 0; i < length; i++) 
	{
		buf[i] = *data;
		data++;
	};
	buf[length] = '\0';
	//log("intbuf-%s", buf);

	return atoi(buf);
};

//16進数を10進数に戻す
int MapCreator::getHexToInt(char* data,int length)
{
	char tmp = *data;

	if ('0' <= tmp && '9' >= tmp) return (tmp - 0x30);//0x30は'0'の文字コード
	if ('A' <= tmp && 'F' >= tmp) return (tmp + 0x0A - 0x41);//0x41は'A'の文字コード
	if ('a' <= tmp && 'f' >= tmp) return (tmp + 0x0A - 0x61);//0x61は'a'の文字コード

	return 0;
}

//特定の文字を探して、配列内の番号を返す
int MapCreator::getFindCharNumber(char* data,char find)
{
	int num = 0;
	for (int i = 0; data[i] != '\0'; i++)
	{
		if (data[i] == find) 
		{
			num = i;
			log("find[%c]/num[%d]", find,i);
			break;
		}
	}
	return num;
};

DIR_DEGREE MapCreator::getCharToDirction(char* dir) 
{
	char temp = *dir;
	switch (temp)
	{
	case 'E'://EAST
		log("E");
		return DIR_DEGREE::DIR_RIGHT;
		break;
	case 'N'://NORTH
	log("N");
		return DIR_DEGREE::DIR_UP;
		break;
	case 'W'://WEST
		log("W");
		return DIR_DEGREE::DIR_LEFT;
		break;
	case 'S'://SOUTH
		log("S");
		return DIR_DEGREE::DIR_DOWN;
		break;
	default:
		break;
	}
};

//マップ内の衝突関係処理
void MapCreator::checkWall(Character* obj, Vector<Wall*>wall, float range) 
{
	for (int i = 0; i < wall.size(); i++) 
	{
		//同じものを入れることはないようにする


		if (length(obj->myPosition-wall.at(i)->getPosition()) < range)
		{
			obj->setTarget(wall.at(i));
			log("check");
		}
	}
};



Layer* MapCreator::printMap() 
{
	log("printStart\n--------------------------------------");
	Layer* layer = Layer::create();
	log("Character\n--------------------------------------");
	layer->addChild(robot,4);
	log("Enemy\n--------------------------------------");
	log("size=%d", enemys.size());
	for (int i = 0; i < enemys.size(); i++)
	{
		Enemy* p = enemys.at(i);
		p->setTarget(robot->rightRobot);
		p->setTarget(robot->leftRobot);
		layer->addChild(p,3);
	}
	log("wall\n--------------------------------------");
	log("size=%d", walls.size());
	for (int i = 0; i < walls.size(); i++)
	{
		robot->rightRobot->setTarget(walls.at(i));
		robot->leftRobot->setTarget(walls.at(i));
		walls.at(i)->setTargets(&robot->rightRobot->myPosition, &robot->leftRobot->myPosition);
		layer->addChild(walls.at(i),2);
	}
	log("floor\n--------------------------------------");
	log("size=%d", floors.size());
	for (int i = 0; i < floors.size(); i++)
	{
		layer->addChild(floors.at(i),0);
	}
	log("createEnd\n--------------------------------------");

	return layer;
};


