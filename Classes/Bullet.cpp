#include "Bullet.h"


Bullet*  Bullet::bullet(){
	Bullet* one = Bullet::create();
	one->sprite = Sprite::create("Projectile.png");
	one->addChild(one->sprite, 0);
	one->setCascadeOpacityEnabled(true);
	return one;
}
/*
void Bullet::trackEnemy(Creep* enemy)
{
//	this->runAction(Sequence::create(MoveTo::create(ccpDistance(enemy->getPosition(), getPosition()) / speed, enemy->getPosition()), CallFuncN::create(this, callfuncN_selector(Bullet::bulletClean)), NULL));
	




}
*/