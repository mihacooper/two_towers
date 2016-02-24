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
    // choice scene
    cocos2d::Vec2 slct_main_label;
    cocos2d::Rect slct_choice_area;
    std::vector<cocos2d::Vec2> slct_all_buildings;
    std::vector<cocos2d::Vec2> slct_selected_buildings;

    // game scene
    std::vector<cocos2d::Vec2> bfld_units;
    std::vector<cocos2d::Vec2> bfld_buildings;
};

struct _GameConfig
{
    unsigned int tower_life;
};

struct _GameState
{
    std::vector<BuildingConfig> fp_buildings;
    unsigned int fp_tower;

    std::vector<BuildingConfig> sp_buildings;
    unsigned int sp_tower;
};

extern cocos2d::Size ScreenResolution;
extern std::vector<BuildingConfig> AllBuildings;
extern std::vector<UnitConfig> AllUnits;
extern _SystemConfig SystemConfig;
extern _GameConfig GameConfig;
extern _GameState GameState;

#endif // UNITS_CONFIG_H
