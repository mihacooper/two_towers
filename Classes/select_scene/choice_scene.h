#ifndef CHOICESCENE_H
#define CHOICESCENE_H

#include <memory>
#include "cocos2d.h"
#include "helpers.h"

class ChoiceScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void NextSceneButton(Ref* pSender);
    bool OnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void OnTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void OnTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    template<typename Container, typename Positions>
    void UpdateObjectsList(Container& container, Positions positions);
    bool IsSelectionFull();

    CREATE_FUNC(ChoiceScene)

protected:
    std::vector<helpers::Building*> m_selectedObjects;
    std::vector<helpers::Building*> m_allObjects;
};

#endif // CHOICESCENE_H
