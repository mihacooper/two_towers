#include "selector.h"

Selector::Selector() : m_objects(6, nullptr)
{}

void Selector::CheckArea(BaseObject* obj)
{
    if(SystemConfig.slct_choice_area.containsPoint(obj->getPosition()))
    {
        for(auto p = m_objects.begin(); p != m_objects.end(); p++)
        {
            if(*p == nullptr)
            {
                *p = obj;
                obj->MoveTo(SystemConfig.slct_selected_buildings[p - m_objects.begin()]);
                return;
            }
        }
    }
    else
    {
        auto pObj = std::find(m_objects.begin(), m_objects.end(), obj);
        if(pObj != m_objects.end())
        {
            *pObj = nullptr;
            for(auto mObj = pObj + 1; mObj != m_objects.end(); mObj++)
            {
                if(*mObj == nullptr) break;
                *(mObj - 1) = *mObj;
                (*mObj)->MoveTo(SystemConfig.slct_selected_buildings[mObj - m_objects.begin()]);
                *mObj = nullptr;
            }
        }
    }
    obj->MoveTo(obj->GetOriginPosition());
}

bool Selector::IsFull()
{
    for(auto& p: m_objects)
        if(p == nullptr)
            return false;
    return true;
}
