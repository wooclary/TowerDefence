#include <fstream>
#include <sstream>
#include <regex>
#include "HelloWorldScene.h"
#include"DataModel.h"
#include "WayPoint.h"
#include "Wave.h"
#include "Creep.h"
#include "GameLogic .h"
#include"Factory.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	
	


	//添加背景和游戏逻辑层
	this->tiledMap = TMXTiledMap::create("test.tmx");
	this->background = tiledMap->layerNamed("Background");

	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	int x = tiledMap->getMapSize().width;
	int y = tiledMap->getMapSize().height;
	glview->setDesignResolutionSize(x*32, y*32, kResolutionExactFit);
	glview->setFrameSize(x * 32, y * 32);

	this->background->setAnchorPoint(Vec2(0, 0));
	this->addChild(tiledMap, 0);

	m_pInstance = DataModel::getInstance();
	m_pInstance->m_tiledMap = tiledMap;
	m_pInstance->m_Background = background;
	
	this->setPath();
	this->setTower();

	auto myGameHUD = GameLogic::getInstance();
	this->addChild(myGameHUD, 1);

	
	this->setWaves();

	//开始产生敌人，进行游戏
//	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::genEnemy), 1.0f);

	return true;
}

void HelloWorld::setPath(){
	auto *objects = this->tiledMap->objectGroupNamed("Objects");
	WayPoint *wp = NULL;
	std::string stringWithFormat = "Waypoint";
	int wayPointCounter = 0;
	ValueMap wayPoint;
	wayPoint = objects->objectNamed(stringWithFormat + std::to_string(wayPointCounter));
	while (wayPoint.begin() != wayPoint.end())
	{
		int x = wayPoint.at("x").asInt();
		int y = wayPoint.at("y").asInt();
		wp = WayPoint::create();
		wp->setPosition(x, y);
		m_pInstance->path.pushBack(wp);
		wayPointCounter++;
		wayPoint = objects->objectNamed(stringWithFormat + std::to_string(wayPointCounter));
	}
	wp = NULL;
}

void HelloWorld::setTower(){
	std::fstream fs("test.tmx");
	std::stringstream ss;
	ss << fs.rdbuf();
	std::string str(ss.str());

	const std::regex pattern(R"delimiter(<object name="Tower." range="(.*?)" power="(.*?)" frequency="(.*?)" attack="(.*?)" />)delimiter");
	std::smatch result;

	TowerDef towerDef;
	auto *m = DataModel::getInstance();
	bool value = std::regex_search(str, result, pattern);

	for (std::sregex_iterator it(str.begin(), str.end(), pattern), end_it; it != end_it;++it){	
		towerDef.range = stoi(it->str(1));
		towerDef.power = stoi(it->str(2));
		towerDef.frequency = stof(it->str(3));
		towerDef.attack = it->str(4) == "MG" ? MG : RA;
		m->towerDefine.push_back(towerDef);
	}
}

void HelloWorld::setWaves()
{
	Wave *wave = NULL;
	//暂不支持混合兵种,以后这里要改成读文件实现
	wave = Wave::create()->initWithCreep(5 + rand_0_1() * 5, 1);
	m_pInstance->waves.pushBack(wave);
	for (int i = 0; i < 24; i++){
		wave = Wave::create()->initWithCreep(5+rand_0_1()*5, 8);
		m_pInstance->waves.pushBack(wave);
	}
	
	//wave = NULL;
//	wave = Wave::create()->initWithCreep(10, 10);
	//m_pInstance->waves.pushBack(wave);
	//wave = NULL;
//	m_pInstance->waves.reverse();
}

void HelloWorld::genEnemy(float dt)
{
	//Wave* wave = this->getCurrentWave();
	
	Wave* wave = m_pInstance->waves.back();
	if (wave->leftTime > 0){
		wave->leftTime--;
		return;
	}
	if (wave->totalCreeps == 0) {
		m_pInstance->waves.popBack();
		if (m_pInstance->waves.size() == 0){
			this->unschedule(schedule_selector(HelloWorld::genEnemy));
		}
		return;
	}
	wave->totalCreeps--;

	Creep *target = NULL;
	int random =  m_pInstance->waves.size()%2;
//	int random = m_pInstance->waves.size() - 1;
	/*if (random == 0)
	{
		target = FastRedCreep::creep();	
	}
	else
	{
		target = StrongGreenCreep::creep();
	}
	*/
	target=Factory::createCreep(random);
	this->addChild(target, 1);
	DataModel::getInstance()->enemys.pushBack(target);
	target->startMove();
}




void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
