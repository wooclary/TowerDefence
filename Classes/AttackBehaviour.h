#pragma once

#include "cocos2d.h"
#include "CCVector.h"
#include "Bullet.h"
#include "Creep.h"

class Tower;

class AttackBehaviour:public Sprite
{
protected:
	Tower* tower;
public: 
	AttackBehaviour(Tower*);
	virtual Vector<Creep*> getTarget()=0;
	virtual void shootProjectiles()=0;
	virtual void attackLogic()=0;
};

class MachineGun:public AttackBehaviour
{
public:
	//static MachineGun* getInstance(Tower*);
	MachineGun(Tower* _tower);
	//bool init();
	Vector<Creep*> getTarget();
	void shootProjectiles();
	void attackLogic();
	//CREATE_FUNC(MachineGun);
};

class Radiation :public AttackBehaviour
{
public:
	//static Radiation* getInstance(Tower*);
	Radiation(Tower*);
	//bool init();
	Vector<Creep*> getTarget();
	void shootProjectiles();
	void attackLogic();
	//CREATE_FUNC(Radiation);
};