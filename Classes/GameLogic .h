#pragma once
#include "cocos2d.h"
#include "DataModel.h"
USING_NS_CC;

class GameLogic: public Layer 
{
public:
	Sprite* towerPanel;   //第一列显示有哪些塔可以被建造，第二列显示要建造的位置
	Vec2 buildPostion;		//用户将要建造塔的目标位置
	TMXTiledMap *tiledMap;
	TMXLayer* backgroundLayer;
	DataModel * m_pInstance;
	

	//可以被选择塔
	Vector<Sprite*> selTowers;
	
	virtual bool init();
	static GameLogic* getInstance();

	//将触摸的位置转到地图上的坐标(和世界坐标系不同)
	Vec2 tileCoordForPosition(Vec2 position);

	//判断这个点是否可以建造塔
	bool canBuildOnTilePosition(Point pos);

	CREATE_FUNC(GameLogic);
	virtual void onEnter();
	bool onTouchBegan(Touch *touch, Event *event);
public:
	static GameLogic* m_logicInstance;
};