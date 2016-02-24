#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"
#include "helpers.h"

class GameScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(Ref* pSender);
    bool OnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void OnTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void OnTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void ReloadUnits();
    void ReloadBuildings();

    CREATE_FUNC(GameScene)

protected:
    std::vector<helpers::Unit*> m_units;
    std::vector<helpers::Building*> m_buildings;
};

#endif // GAMESCENE_H
