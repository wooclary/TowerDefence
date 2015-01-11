#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "DataModel.h"
#include "Struct.h"

USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
	
	TMXTiledMap* tiledMap;	//��ȡtiled���ɵ�tmx�ļ�
	TMXLayer* background;	//��ȡ����
	DataModel * m_pInstance;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();


    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	
	TMXTiledMap* getTiledMap(){
		return tiledMap;
	}
	TMXLayer* getBackground(){
		return background;
	}
	//��TMX�ļ��ж�ȡ·���㣬��������������
	void setPath();

	void setTower();

	//�����м������˺�����
	void setWaves();

	//�������˵ľ���ʵ��
	void genEnemy(float dt);

	

	

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
