#pragma once
#include "cocos2d.h"
#include "WayPoint.h"
#include "Bullet.h"
USING_NS_CC;

class Creep: public Sprite 
{
public:
	int curHp;			//当前的血量	
	int speed;			//移动速度
	int curWaypoint;	//现在处于的路径点的索引
	//int tag;
	Sprite* sprite;		//加载图片的精灵
	virtual bool init();
	Creep* initWithCreep(Creep* copyFrom);
	WayPoint* getNextWaypoint();
	WayPoint* getCurrentWaypoint();

	/*开始行走*/
	void Creep::startMove();

	/*使小兵沿着设定的路径行走*/
	void FollowPath(Node* sender);

	/*
	*/
	void die();
	CREATE_FUNC(Creep);
};

class FastRedCreep: public Creep 
{
public:
	static Creep* creep();
};

class StrongGreenCreep: public Creep
{
public:
	static Creep* creep();
};