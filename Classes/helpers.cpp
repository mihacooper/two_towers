#include "helpers.h"

namespace helpers {

void MoveTo(cocos2d::Sprite* obj, const cocos2d::Vec2& pos)
{
    auto action = cocos2d::MoveTo::create(0.15, pos);
    obj->runAction(action);
}

std::vector<BuildingConfig> CopyBuildings(std::vector<Building*> objects)
{
    std::vector<BuildingConfig> copy;
    for(auto& obj : objects)
        copy.push_back(obj->m_properties);
    return copy;
}

}
