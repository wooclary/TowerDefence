#pragma once
#include "cocos2d.h"
#include "WayPoint.h"
#include "Bullet.h"
USING_NS_CC;

class Creep: public Sprite 
{
public:
	int curHp;			//��ǰ��Ѫ��	
	int speed;			//�ƶ��ٶ�
	int curWaypoint;	//���ڴ��ڵ�·���������
	//int tag;
	Sprite* sprite;		//����ͼƬ�ľ���
	virtual bool init();
	Creep* initWithCreep(Creep* copyFrom);
	WayPoint* getNextWaypoint();
	WayPoint* getCurrentWaypoint();

	/*��ʼ����*/
	void Creep::startMove();

	/*ʹС�������趨��·������*/
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