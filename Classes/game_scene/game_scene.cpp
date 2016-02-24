#include "game_scene.h"
#include "config.h"
#include "helpers.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

void GameScene::ReloadUnits()
{
    for(auto unit : m_units)
        this->removeChild(unit);
    m_units.clear();

    std::vector<UnitConfig> unitConfigs;
    for(auto build : GameState.fp_buildings)
    {
        (void)build;
        unitConfigs.push_back(AllUnits[0]);
        unitConfigs.push_back(AllUnits[0]);
    }

    for(auto unitIter = unitConfigs.begin(); unitIter != unitConfigs.end(); unitIter++)
    {
        auto unit = *unitIter;
        auto unitObject = helpers::CreateObject<GameScene, UnitConfig>(unit.image, this, unit);
        unitObject->setPosition(SystemConfig.bfld_units[unitIter - unitConfigs.begin()]);
        this->addChild(unitObject, 0);
        m_units.push_back(unitObject);
    }
}

void GameScene::ReloadBuildings()
{
    for(auto build : m_buildings)
        this->removeChild(build);
    m_buildings.clear();

    for(auto buildIter = GameState.fp_buildings.begin(); buildIter != GameState.fp_buildings.end(); buildIter++)
    {
        auto build = *buildIter;
        auto buildObject = helpers::CreateObject<GameScene, BuildingConfig>(build.image, this, build);
        buildObject->setPosition(SystemConfig.bfld_buildings[buildIter - GameState.fp_buildings.begin()]);
        this->addChild(buildObject, 0);
        m_buildings.push_back(buildObject);
    }
}

bool GameScene::init()
{
    if (!LayerColor::initWithColor(Color4B(10, 10, 10, 255)))
        return false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2, origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    ReloadBuildings();
    ReloadUnits();
    return true;
}

bool GameScene::OnTouchBegan(Touch* touch, Event* event)
{
    return false;
}

void GameScene::OnTouchMoved(Touch* touch, Event* event)
{
}

void GameScene::OnTouchEnded(Touch* touch, Event* event)
{
}

void GameScene::menuCloseCallback(Ref* pSender)
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
