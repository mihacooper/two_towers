#include "choice_scene.h"
#include "config.h"
#include "game_scene/game_scene.h"

#include <vector>

USING_NS_CC;

static int TopShift;
static int LeftShift;
static const int FrameBorder = 20;
static const int ImgWidth = 100;
static const int ImgHeight = 100;

class HelpObject : public Sprite
{
public:
    virtual bool OnTouchBegan(Touch* touch, Event* event)
    {
        return true;
    }
};

class BuildSelector : public BaseObject
{
public:
    BuildSelector(std::shared_ptr<Selector> mngr, std::string help) : BaseObject(mngr) {}

    virtual void OnClick(Touch* touch, Event* event)
    {
        cocos2d::MessageBox(m_help.c_str(), "Description");
    }

protected:
    std::string m_help;
};

Scene* ChoiceScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ChoiceScene::create();
    scene->addChild(layer);
    return scene;
}

bool ChoiceScene::init()
{
    if (!LayerColor::initWithColor(ccc4(10, 10, 10, 255)))
        return false;

    TopShift = Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height - 150;
    LeftShift = Director::getInstance()->getVisibleOrigin().x + 150;

    m_selector = std::make_shared<Selector>();

    auto label = Label::createWithTTF("Select buildings", "fonts/Marker Felt.ttf", 32);
    label->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
                            (TopShift + Director::getInstance()->getVisibleSize().height) / 2 + label->getHeight() / 2));
    this->addChild(label, 1);

    auto buttonNext = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(ChoiceScene::NextSceneButton, this));
    buttonNext->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 10 + buttonNext->getContentSize().height / 2));
    auto menu = Menu::create(buttonNext, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    int buildInLine = 6;
    for(unsigned int i = 0; i < AllBuildings.size(); i++)
    {
        int x = i % buildInLine;
        int y = -(i / buildInLine);
        auto build = CreateObject<BuildSelector, std::shared_ptr<Selector>>(AllBuildings[i].image, m_selector, "This is help!");
        build->SetOriginPosition(SystemConfig.slct_curr_buildings[i]);
        this->addChild(build, 0);
    }
    return true;
}

void ChoiceScene::NextSceneButton(Ref* pSender)
{
    if(m_selector->IsFull())
    {
        auto scene = GameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}
