#include "choice_scene.h"
#include "config.h"
#include "game_scene/game_scene.h"
#include "helpers.h"

#include <vector>
#include <numeric>
#include <algorithm>

USING_NS_CC;

static int TopShift;
static int LeftShift;
static const int FrameBorder = 20;
static const int ImgWidth = 100;
static const int ImgHeight = 100;

Scene* ChoiceScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ChoiceScene::create();
    scene->addChild(layer);
    return scene;
}

bool ChoiceScene::init()
{
    if (!LayerColor::initWithColor(Color4B(10, 10, 10, 255)))
        return false;

    TopShift = Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height - 150;
    LeftShift = Director::getInstance()->getVisibleOrigin().x + 150;

    auto label = Label::createWithTTF("Select buildings", "fonts/Furgatorio.ttf", 80);
    label->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
                            (TopShift + Director::getInstance()->getVisibleSize().height) / 2 + label->getHeight() / 2));
    this->addChild(label, 1);

    auto buttonNext = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(ChoiceScene::NextSceneButton, this));
    buttonNext->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 10 + buttonNext->getContentSize().height / 2));
    auto menu = Menu::create(buttonNext, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    for(unsigned int i = 0; i < AllBuildings.size(); i++)
    {
        auto build = helpers::CreateObject<ChoiceScene, BuildingConfig>(AllBuildings[i].image, this, AllBuildings[i]);
        build->setPosition(SystemConfig.slct_all_buildings[i]);
        this->addChild(build, 0);
        m_allObjects.push_back(build);
    }
    m_selectedObjects.resize(SystemConfig.slct_selected_buildings.size());
    return true;
}

void ChoiceScene::NextSceneButton(Ref* pSender)
{
    if(true || IsSelectionFull())
    {
        if(GameState.first_player.buildings.size() == 1U)
        {
            auto toAdd = {AllBuildings[1],AllBuildings[1],AllBuildings[1],AllBuildings[1],AllBuildings[1],AllBuildings[1]};//helpers::CopyBuildings(m_selectedObjects);
            GameState.first_player.buildings.insert(GameState.first_player.buildings.end(), toAdd.begin(), toAdd.end());
            auto scene = ChoiceScene::createScene();
            Director::getInstance()->replaceScene(scene);
        }
        else
        {
            auto toAdd = {AllBuildings[1],AllBuildings[1],AllBuildings[1],AllBuildings[1],AllBuildings[1],AllBuildings[1]};//helpers::CopyBuildings(m_selectedObjects);
            GameState.second_player.buildings.insert(GameState.second_player.buildings.end(), toAdd.begin(), toAdd.end());
            auto fpBaseScene = GameScene::createScene();
            auto spBaseScene = GameScene::createScene();
            auto fpScene = dynamic_cast<GameScene*>(fpBaseScene->getChildByTag(0));
            auto spScene = dynamic_cast<GameScene*>(spBaseScene->getChildByTag(0));
            fpScene->Init(spBaseScene, &GameState.first_player, &GameState.second_player);
            spScene->Init(fpBaseScene, &GameState.second_player, &GameState.first_player);
            Director::getInstance()->replaceScene(fpBaseScene);
        }
    }
}

bool ChoiceScene::OnTouchBegan(Touch* touch, Event* event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    if (rect.containsPoint(locationInNode))
    {
        auto obj1 = std::find(m_selectedObjects.begin(), m_selectedObjects.end(), target);
        auto obj2 = std::find(m_allObjects.begin(),      m_allObjects.end(),      target);
        if(obj1 != m_selectedObjects.end()) *obj1 = nullptr;
        if(obj2 != m_allObjects.end())      *obj2 = nullptr;
        return true;
    }
    return false;
}

void ChoiceScene::OnTouchMoved(Touch* touch, Event* event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    target->setPosition(target->getPosition() + touch->getDelta());
}

void ChoiceScene::OnTouchEnded(Touch* touch, Event* event)
{
    auto obj = static_cast<helpers::Building*>(event->getCurrentTarget());
    std::vector<helpers::Building*>* objects;
    std::vector<Vec2>* positions;

    if(SystemConfig.slct_choice_area.containsPoint(obj->getPosition()) && !IsSelectionFull())
    {
        objects = &m_selectedObjects;
        positions = &SystemConfig.slct_selected_buildings;
    }
    else
    {
        objects = &m_allObjects;
        positions = &SystemConfig.slct_all_buildings;
    }
    auto firstEmpty = std::find(objects->begin(), objects->end(), nullptr);
    if(firstEmpty != objects->end())
    {
        *firstEmpty = obj;
        helpers::MoveTo(obj, (*positions)[firstEmpty - objects->begin()]);
    }
    UpdateObjectsList(m_allObjects, SystemConfig.slct_all_buildings);
    UpdateObjectsList(m_selectedObjects, SystemConfig.slct_selected_buildings);
}

template<typename Container, typename Positions>
void ChoiceScene::UpdateObjectsList(Container& container, Positions positions)
{
    for(auto iter = container.begin(); iter != container.end() - 1; iter++)
    {
        if(*iter == nullptr)
        {
            std::swap(*iter, *(iter + 1));
            if(*iter)
                helpers::MoveTo(*iter, positions[iter - container.begin()]);
        }
    }
}

bool ChoiceScene::IsSelectionFull()
{
    return std::accumulate(m_selectedObjects.begin(), m_selectedObjects.end(), true,
            [](bool state, Sprite* iter) { return state && (iter != nullptr); });
}
