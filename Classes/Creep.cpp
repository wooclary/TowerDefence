#include "Creep.h"
#include "WayPoint.h"
#include "DataModel.h"

USING_NS_CC;

bool Creep::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setCascadeOpacityEnabled(true);
	curWaypoint = 0;
	return true;
}

Creep* Creep::initWithCreep(Creep* copyFrom)
{
	return NULL;
}

Creep* FastRedCreep::creep()
{
	Creep* creep = Creep::create();
	creep->sprite = Sprite::create("Enemy1.png");
	creep->addChild(creep->sprite, 0);
	creep->curHp = 20;
	creep->speed = 100;
	return creep;
}

Creep* StrongGreenCreep::creep()
{
	Creep* creep = create();
	creep->sprite = Sprite::create("Enemy2.png");
	creep->addChild(creep->sprite, 0);
	creep->curHp = 50;
	creep->speed = 50;
	return creep;
}

WayPoint* Creep::getCurrentWaypoint()
{
	DataModel* m = DataModel::getInstance();
	WayPoint* waypoint = (WayPoint *)m->path.at(curWaypoint);
	return waypoint;
}

WayPoint* Creep::getNextWaypoint()
{
	DataModel* m = DataModel::getInstance();
	int lastWaypoint = (int)m->path.size();
	this->curWaypoint++;
	if (this->curWaypoint >= lastWaypoint){
		this->runAction(CCHide::create());
		m->enemys.eraseObject(this);
		return NULL;
	}
	WayPoint *waypoint = (WayPoint *)m->path.at(curWaypoint);
	return waypoint;
}

void Creep::startMove(){
	WayPoint *wayPoint = getCurrentWaypoint();
	WayPoint *nextWayPoint = getNextWaypoint();
	setPosition(wayPoint->getPosition());
	auto actionMove = CCMoveTo::create(wayPoint->getPosition().getDistance(nextWayPoint->getPosition()) / speed, nextWayPoint->getPosition());
	auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(Creep::FollowPath));
	runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}

void Creep::FollowPath(Node* sender)
{
	Creep *creep = (Creep *)sender;
	WayPoint * nextWayPoint = creep->getNextWaypoint();
	if (nextWayPoint == NULL){
		return;
	}
	auto actionMove = MoveTo::create(creep->getPosition().getDistance(nextWayPoint->getPosition()) / creep->speed, 
										nextWayPoint->getPosition());
	auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(Creep::FollowPath));
	creep->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

void Creep::die(){

	stopAllActions();
	runAction(Sequence::create(Blink::create(0.5, 1), FadeOut::create(0.1f), NULL));
	DataModel::getInstance()->enemys.eraseObject(this);
}

