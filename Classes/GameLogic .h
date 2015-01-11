#pragma once
#include "cocos2d.h"
#include "DataModel.h"
USING_NS_CC;

class GameLogic: public Layer 
{
public:
	Sprite* towerPanel;   //��һ����ʾ����Щ�����Ա����죬�ڶ�����ʾҪ�����λ��
	Vec2 buildPostion;		//�û���Ҫ��������Ŀ��λ��
	TMXTiledMap *tiledMap;
	TMXLayer* backgroundLayer;
	DataModel * m_pInstance;
	

	//���Ա�ѡ����
	Vector<Sprite*> selTowers;
	
	virtual bool init();
	static GameLogic* getInstance();

	//��������λ��ת����ͼ�ϵ�����(����������ϵ��ͬ)
	Vec2 tileCoordForPosition(Vec2 position);

	//�ж�������Ƿ���Խ�����
	bool canBuildOnTilePosition(Point pos);

	CREATE_FUNC(GameLogic);
	virtual void onEnter();
	bool onTouchBegan(Touch *touch, Event *event);
public:
	static GameLogic* m_logicInstance;
};