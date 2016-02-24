#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>

#include "cocos2d.h"
#include "config.h"

namespace helpers {

void MoveTo(cocos2d::Sprite* obj, const cocos2d::Vec2& pos);

//template<typename T>
//class PropertyObject;

template<typename Properties>
class PropertyObject : public cocos2d::Sprite
{
public:
    template<typename Handler, typename Property>
    friend PropertyObject<Property>* CreateObject(std::string, Handler*, const Property&);

    PropertyObject(const Properties& prop) : m_properties(prop) { }
    Properties m_properties;
};

typedef struct{} EmptyType;
typedef PropertyObject<BuildingConfig> Building;
typedef PropertyObject<UnitConfig>     Unit;

template<typename Handler, typename Property = EmptyType>
PropertyObject<Property>* CreateObject(std::string image, Handler* handler, const Property& prop = Property())
{
    using namespace std::placeholders;
    PropertyObject<Property>* sprite = new (std::nothrow) PropertyObject<Property>(prop);
    if (sprite && sprite->initWithFile(image))
    {
        sprite->autorelease();
        auto listener = cocos2d::EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = std::bind(&Handler::OnTouchBegan, handler, _1, _2);
        listener->onTouchMoved = std::bind(&Handler::OnTouchMoved, handler, _1, _2);
        listener->onTouchEnded = std::bind(&Handler::OnTouchEnded, handler, _1, _2);
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
        return sprite;
    }
    std::cout << "Unable to initialize object with image " << image << std::endl;
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

std::vector<BuildingConfig> CopyBuildings(std::vector<Building*> objects);

}

#endif // HELPERS_H
