#pragma once
#include "cocos2d.h"
#include "Creep.h"
#include "Tower.h"
#include "Struct.h"

USING_NS_CC;

class Factory : public Node
{
public:
	int curHp;			//当前的血量	
	int speed;			//移动速度
	int curWaypoint;	//现在处于的路径点的索引
	//int tag;
	
	virtual bool init();
	static Creep* createCreep(int );
	static Tower* createTower(TowerDef );
	

	
	CREATE_FUNC(Factory);
};

