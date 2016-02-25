#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"
#include "helpers.h"

class GameScene : public cocos2d::LayerColor
{
public:
    GameScene() : m_anotherPlayerScene(NULL), m_playerConfig(NULL), m_enemyConfig(NULL) {}
    static cocos2d::Scene* createScene();
    virtual bool Init(cocos2d::Scene* anotherPlayerScene, PlayerConfig* playerConfig, PlayerConfig* enemyConfig);
    void menuCloseCallback(Ref* pSender);
    bool OnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void OnTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void OnTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void ReloadUnits();
    void ReloadBuildings();
    void UseUnit(helpers::Unit* unit);

protected:
    UnitConfig* FindUnit(std::string name);

    std::vector<helpers::Unit*> m_units;
    std::vector<helpers::Building*> m_buildings;
    cocos2d::Scene* m_anotherPlayerScene;
    PlayerConfig* m_playerConfig;
    PlayerConfig* m_enemyConfig;
};

#endif // GAMESCENE_H
