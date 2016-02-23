#ifndef CHOICESCENE_H
#define CHOICESCENE_H

#include <memory>
#include "cocos2d.h"
#include "base_object.h"
#include "selector.h"

class ChoiceScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ChoiceScene)
    void NextSceneButton(Ref* pSender);
protected:
    std::shared_ptr<Selector> m_selector;
};

#endif // CHOICESCENE_H
