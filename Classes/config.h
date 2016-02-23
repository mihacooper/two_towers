#ifndef UNITS_CONFIG_H
#define UNITS_CONFIG_H

#include <string>
#include <vector>

#include "cocos2d.h"

struct UnitConfig
{
    std::string image;
};

struct BuildingConfig
{
    std::string image;
    std::string name;
    std::string help;
};

struct _SystemConfig
{
    cocos2d::Vec2 slct_main_label;
    cocos2d::Rect slct_choice_area;
    std::vector<cocos2d::Vec2> slct_curr_buildings;
    std::vector<cocos2d::Vec2> slct_selected_buildings;
};

extern cocos2d::Size ScreenResolution;
extern std::vector<BuildingConfig> AllBuildings;
extern _SystemConfig SystemConfig;


#endif // UNITS_CONFIG_H
