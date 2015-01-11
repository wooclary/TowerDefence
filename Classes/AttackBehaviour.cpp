#include "AttackBehaviour.h"
#include "DataModel.h"
#include "Tower.h"

AttackBehaviour::AttackBehaviour(Tower* _tower){
	this->tower = _tower;
}

MachineGun::MachineGun(Tower* _tower) :AttackBehaviour(_tower){

}

Vector<Creep*> MachineGun::getTarget(){
	Vector<Creep*> temp_targets;
	temp_targets.clear();
	DataModel* m = DataModel::getInstance();

	if (!tower->targets.empty()&& m->enemys.contains(tower->targets.front())){
		for (auto target : tower->targets){
			if (ccpDistance(tower->getPosition(), target->getPosition()) < tower->range){
				temp_targets.pushBack(target);
				return temp_targets;
			}
		}
	}

	for (auto candidate : m->enemys)
	{
		double curDistance = ccpDistance(tower->getPosition(), candidate->getPosition());
		if (curDistance < tower->range){
			temp_targets.pushBack(candidate);
			return temp_targets;
		}
	}
	return temp_targets;
}

void MachineGun::shootProjectiles(){
	DataModel *m = DataModel::getInstance();

	if (!tower->targets.empty() && tower->targets.front()->curHp > 0)
	{
		Bullet *nextProjectile = Bullet::bullet();
		nextProjectile->setPosition(tower->getPosition());
		tower->getParent()->addChild(nextProjectile, 1);

		float speed = 500;
		float delta = 0.1f;
		Point shootVector = -(tower->targets.front()->getPosition() - tower->getPosition());
		Point normalizedShootVector = ccpNormalize(shootVector);
		Point overshotVector = normalizedShootVector * 320;
		Point offscreenPoint = (tower->getPosition() - overshotVector);

		nextProjectile->runAction(Sequence::create(MoveTo::create(delta, tower->targets.front()->getPosition()), FadeOut::create(0.1f), NULL));
		//nextProjectile->runAction(Sequence::create(MoveTo::create(delta, offscreenPoint), FadeOut::create(1), NULL));
		tower->targets.front()->curHp -= tower->power;

		if (tower->targets.front()->curHp <= 0){
			tower->targets.front()->die();
			tower->targets.clear();
		}
	}
}

void MachineGun::attackLogic()
{

	tower->targets = this->getTarget();
	if (!tower->targets.empty())
	{
		// Rotate player to face shooting direction
		Point shootVector = tower->targets.front()->getPosition() - tower->getPosition();
		float shootAngle = ccpToAngle(shootVector);
		float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);

		float rotateSpeed = 0.2;
		float rotateDuration = fabs(shootAngle * rotateSpeed);
		tower->runAction(Sequence::create(RotateTo::create(rotateDuration, cocosAngle), 
			CallFunc::create(this, callfunc_selector(MachineGun::shootProjectiles)), NULL));
	}
}

Radiation::Radiation(Tower* _tower) :AttackBehaviour(_tower){

}

Vector<Creep*> Radiation::getTarget(){
	Vector<Creep*> temp_targets;
	temp_targets.clear();
	DataModel* m = DataModel::getInstance();

	for (auto candidate : m->enemys)
	{
		double curDistance = ccpDistance(tower->getPosition(), candidate->getPosition());
		if (curDistance < tower->range){
			temp_targets.pushBack(candidate);
		}
	}
	return temp_targets;
}

void Radiation::shootProjectiles(){
	DataModel *m = DataModel::getInstance();
	
	if (!tower->targets.empty())
	{
		Sprite* radiProjectiles = Sprite::create("Range.png");
		radiProjectiles->setScale(0.1);
		radiProjectiles->setPosition(tower->getPosition());
		tower->getParent()->addChild(radiProjectiles,3);
		radiProjectiles->setVisible(false);
		radiProjectiles->runAction(Sequence::create(Show::create(),FadeIn::create(0.1),
			ScaleTo::create(0.8, tower->range / 50),FadeOut::create(0.3), NULL));
		for (auto target : tower->targets){
			if (target->curHp > 0){
				target->curHp -= tower->power;
				if (target->curHp <= 0){
					target->die();
				}
			}
		}
	}
}

void Radiation::attackLogic()
{
	tower->targets.clear();
	tower->targets = this->getTarget();
	if (!tower->targets.empty())
	{
		tower->runAction(CallFunc::create(this, callfunc_selector(MachineGun::shootProjectiles)));
	}
}