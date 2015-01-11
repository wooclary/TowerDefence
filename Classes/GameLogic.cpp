#include "GameLogic .h"
#include "DataModel.h"
#include "Tower.h"
#include "Factory.h"

GameLogic* GameLogic::m_logicInstance;

bool GameLogic::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_pInstance = DataModel::getInstance();

	// Draw the background of the game HUD
//	CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB565);
	towerPanel = Sprite::create("towerPanel.png");
	//towerPanel->setAnchorPoint(ccp(0, 0));
	this->addChild(towerPanel, 3);
	//	background->setScaleX(2);
	
	
//	CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_Default);

	// Load the images of the towers we'll have and draw them to the game HUD layer
	//以后要做成读取图片
	Vector<String*> images;

	for (auto item : m_pInstance->towerDefine){
		switch (item.attack){
		case MG:
			images.pushBack(StringMake("MachineGunTurret.png"));
			break;
		case RA:
			images.pushBack(StringMake("RadiationTurret.png"));
			break;
		}
		/*images.pushBack(StringMake("MachineGunTurret.png"));
		images.pushBack(StringMake("RadiationTurret.png"));
		images.pushBack(StringMake("MachineGunTurret.png"));
		images.pushBack(StringMake("MachineGunTurret.png"));*/
	}
	Sprite *sprite;
	for (int i = 0; i < images.size(); ++i)
	{
		String* image = images.at(i);
		sprite = Sprite::create(image->getCString());
		Vec2 towerSize = sprite->getContentSize();
		sprite->setPosition(Vec2((i - (images.size() - images.size()%2-1) / 2) * towerSize.x, towerSize.y * 3 / 2.0));
		towerPanel->addChild(sprite);
		//给不同类型的塔加上标签，方便在建塔的时候判别用户选取的到底是哪个塔
		sprite->setTag(i);
		selTowers.pushBack(sprite);
	}
	towerPanel->setVisible(false);
	return true;
}

GameLogic* GameLogic::getInstance()
{
	if (m_logicInstance == NULL)
	{
		m_logicInstance = GameLogic::create();

	}
	return m_logicInstance;
}

void GameLogic::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameLogic::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameLogic::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLogic::onTouchEnded, this);

	auto dispatcher = Director::getInstance()->getEventDispatcher();

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//dispatcher->addEventListenerWithFixedPriority(listener, 0);
	tiledMap = m_pInstance->m_tiledMap;
	backgroundLayer = m_pInstance->m_Background;

}

Vec2 GameLogic::tileCoordForPosition(Vec2 position)
{
	int x = position.x / (tiledMap->getTileSize().width);
	int y = ((tiledMap->getMapSize().height * tiledMap->getTileSize().height) - position.y) / tiledMap->getTileSize().height;
	return Vec2(x, y);
}

bool GameLogic::canBuildOnTilePosition(Point pos)
{
	Point towerLoc = this->tileCoordForPosition(pos);
	int tileGid = backgroundLayer->getTileGIDAt(towerLoc);
	Value props = this->tiledMap->getPropertiesForGID(tileGid);
	if (props.isNull()){
		return false;
	}
	ValueMap map = props.asValueMap();
	int type_int;
	if (map.size() == 0)
	{
		type_int = 0;
	}
	else
	{
		type_int = map.at("buildable").asInt();
	}

	if (1 == type_int)
	{
		return true;
	}
	return false;
}

bool GameLogic::onTouchBegan(Touch *touch, Event *event)
{
	Point touchLocation = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));
	//得到标准化之后的坐标
	Vec2 targetPoint = tileCoordForPosition(convertTouchToNodeSpace(touch));
	//如果不是可以建造的地区,后续可以加判定是否已经有塔.
	if (!canBuildOnTilePosition(touchLocation) && !towerPanel->isVisible())
	{
		return false;
	}
	if (!towerPanel->isVisible()){
		buildPostion = Vec2((targetPoint.x * 32) + 16, tiledMap->getContentSize().height - (targetPoint.y * 32) - 16);
		towerPanel->setPosition(buildPostion);
		towerPanel->setVisible(true);

	}
	else{
		int i = 0;
		for (auto p:selTowers)
		{
			Point touchInPanel = towerPanel->convertToNodeSpace(convertTouchToNodeSpace(touch));
			Rect v = p->getBoundingBox();
			if (v.containsPoint(touchInPanel)){
				
				//Sprite* tower = Sprite::create("MachineGunTurret.png");
				Sprite* tower = Factory::createTower(m_pInstance->towerDefine[i]);
				this->addChild(tower,2);
				m_pInstance->builedTowers.pushBack(tower);
				tower->setVisible(true);
				tower->setPosition(buildPostion);
			}
			i++;
		}
		towerPanel->setVisible(false);
		
	}
	return true;
}
