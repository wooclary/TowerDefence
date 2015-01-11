#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "DataModel.h"
#include "Struct.h"

USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
	
	TMXTiledMap* tiledMap;	//读取tiled生成的tmx文件
	TMXLayer* background;	//读取背景
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
	//从TMX文件中读取路径点，并存入数据类中
	void setPath();

	void setTower();

	//设置有几波敌人和种类
	void setWaves();

	//产生敌人的具体实现
	void genEnemy(float dt);

	

	

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
