#include "game_scene.h"
#include "config.h"
#include "helpers.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = new(std::nothrow) GameScene();
    layer->autorelease();
    layer->setTag(0);
    scene->addChild(layer);
    return scene;
}

UnitConfig* GameScene::FindUnit(std::string name)
{
    for(auto& unit : AllUnits)
    {
        if(unit.name == name)
            return &unit;
    }
    return nullptr;
}

void GameScene::ReloadUnits()
{
    for(auto unit : m_units)
        this->removeChild(unit);
    m_units.clear();

    std::vector<UnitConfig> unitConfigs;
    for(auto build : m_playerConfig->buildings)
    {
        for(auto unitName : build.states[build.level].objects)
        {
            auto unit = FindUnit(unitName);
            if(unit == nullptr)
                std::cout << "Can't find unit - " << unitName << std::endl;
            unitConfigs.push_back(*unit);
        }
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

    for(auto buildIter = m_playerConfig->buildings.begin(); buildIter != m_playerConfig->buildings.end(); buildIter++)
    {
        auto build = *buildIter;
        auto buildObject = helpers::CreateObject<GameScene, BuildingConfig>(build.image, this, build);
        buildObject->setPosition(SystemConfig.bfld_buildings[buildIter - m_playerConfig->buildings.begin()]);
        this->addChild(buildObject, 0);
        m_buildings.push_back(buildObject);
    }
}

bool GameScene::Init(cocos2d::Scene* anotherPlayerScene, PlayerConfig* playerConfig, PlayerConfig* enemyConfig)
{
    if (!LayerColor::initWithColor(Color4B(10, 10, 10, 255)))
        return false;

    m_anotherPlayerScene = anotherPlayerScene;
    m_playerConfig = playerConfig;
    m_enemyConfig = enemyConfig;

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

void GameScene::UseUnit(helpers::Unit* unit)
{
    this->removeChild(unit);
}

bool GameScene::OnTouchBegan(Touch* touch, Event* event)
{
    auto target = dynamic_cast<helpers::Unit*>(event->getCurrentTarget());
    if(target == nullptr) return false;

    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    if (rect.containsPoint(locationInNode))
    {
        auto res = std::find(m_units.begin(), m_units.end(), target);
        if(res != m_units.end()) *res = nullptr;
        return true;
    }
    return false;
}

void GameScene::OnTouchMoved(Touch* touch, Event* event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    target->setPosition(target->getPosition() + touch->getDelta());
}

void GameScene::OnTouchEnded(Touch* touch, Event* event)
{
    auto obj = static_cast<helpers::Unit*>(event->getCurrentTarget());
    if(obj == nullptr) return;

    if(SystemConfig.bfld_choice_area.containsPoint(obj->getPosition()))
    {
        UseUnit(obj);
    }
    else
    {
        auto firstEmpty = std::find(m_units.begin(), m_units.end(), nullptr);
        if(firstEmpty != m_units.end())
        {
            *firstEmpty = obj;
            helpers::MoveTo(obj, SystemConfig.bfld_units[firstEmpty - m_units.begin()]);
        }
    }
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
