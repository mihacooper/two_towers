#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <iostream>
#include <memory>
#include "cocos2d.h"

#include "config.h"

USING_NS_CC;

template<typename Object, typename ...Args>
Object* CreateObject(std::string image, Args...args)
{
    Object* sprite = new (std::nothrow) Object(args...);
    if (sprite && sprite->initWithFile(image))
    {
        sprite->autorelease();
        return sprite;
    }
    std::cout << "Unable to initialize object with image " << image << std::endl;
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


class BaseObject : public Sprite
{
public:
    class BaseManager
    {
    public:
        virtual void CheckArea(BaseObject*) { /* Add action */ }
    };

    template<typename Object, typename ...Args>
    friend Object* CreateObject(std::string image, Args...args);

    BaseObject(std::shared_ptr<BaseManager> manager) : m_drag(false), m_draggable(true), m_manager(manager)
    {
        using namespace std::placeholders;
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = std::bind(&BaseObject::OnTouchBegan, this, _1, _2);
        listener->onTouchMoved = std::bind(&BaseObject::OnTouchMoved, this, _1, _2);
        listener->onTouchEnded = std::bind(&BaseObject::OnTouchEnded, this, _1, _2);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }

    virtual bool OnTouchBegan(Touch* touch, Event* event)
    {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode))
            return true;
        return false;
    }

    virtual void OnTouchMoved(Touch* touch, Event* event)
    {
        m_drag = true;
        if(m_draggable)
        {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            target->setPosition(target->getPosition() + touch->getDelta());
        }
    }

    virtual void OnTouchEnded(Touch* touch, Event* event)
    {
        if(m_drag)
        {
            m_drag = false;
            m_manager->CheckArea(this);
        }
        else
        {
            OnClick(touch, event);
        }
    }

    virtual void OnClick(Touch* touch, Event* event)
    {}

    virtual void MoveTo(const Vec2& pos)
    {
        auto action = cocos2d::MoveTo::create(0.15, pos);
        this->runAction(action);
    }

    void SetOriginPosition(const Vec2& pos)
    {
        m_originPos = pos;
        this->setPosition(pos);
    }

    Vec2 GetOriginPosition()
    {
        return m_originPos;
    }

protected:
    bool m_drag;
    bool m_draggable;
    std::shared_ptr<BaseManager> m_manager;
    Vec2 m_originPos;
};

#endif // UNIT_H
