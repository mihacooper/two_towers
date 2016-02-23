#ifndef SELECTOR_H
#define SELECTOR_H

#include "base_object.h"
#include "config.h"

class Selector : public BaseObject::BaseManager
{
public:
    Selector();
    void CheckArea(BaseObject* obj) override;
    bool IsFull();

protected:
    std::vector<BaseObject*> m_objects;
};

#endif // SELECTOR_H
