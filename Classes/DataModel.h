#pragma once
#include "cocos2d.h"
#include "CCVector.h"
#include "WayPoint.h"
#include "Wave.h"
#include "Struct.h"

USING_NS_CC;

class DataModel 
{
public:

	//Layer* gameLayer;		//当前运行的游戏场景
//	GameHUD*       _gameHUDLayer;
	TMXTiledMap *m_tiledMap;
	TMXLayer* m_Background;
	std::vector<TowerDef> towerDefine;
	Vector<WayPoint*> path;  //存储一个个路径点(WayPoint类型)
	Vector<Creep*> enemys;
	Vector<Wave*> waves;     //设置有几波敌人和每波敌人的类型
	//已经建造的塔
	Vector<Sprite*> builedTowers;
//	Vector<Projectile*> projectiles;
	static DataModel* getInstance();
private:
	DataModel(){};
	static DataModel * m_pInstance;
};