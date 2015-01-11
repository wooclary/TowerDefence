#include "Wave.h"

USING_NS_CC;

bool Wave::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

Wave* Wave::initWithCreep(  int TotalCreeps,double leftTime)
{
	//this->creepType = creep;
	
	this->totalCreeps = TotalCreeps;
	this->leftTime = leftTime;
	return this;
}

