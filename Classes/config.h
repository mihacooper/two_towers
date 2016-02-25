#ifndef UNITS_CONFIG_H
#define UNITS_CONFIG_H

#include <string>
#include <vector>

#include "cocos2d.h"

struct UnitConfig
{
    std::string name;
    std::string image;
};

struct BuildingConfig
{
    struct BuildingState
    {
        std::string image;
        std::string help;
        std::vector<std::string> objects;
    };

    std::string name;
    std::string image;
    std::string help;
    unsigned int level;
    std::vector<BuildingState> states;
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
    cocos2d::Rect bfld_choice_area;
};

struct PlayerConfig
{
    unsigned int tower_life;
    unsigned int wall_life;
    std::vector<BuildingConfig> buildings;
};

struct _GameConfig
{
    unsigned int initial_tower_life;
    unsigned int initial_wall_life;
};

struct _GameState
{
    PlayerConfig first_player;
    PlayerConfig second_player;
};

extern cocos2d::Size ScreenResolution;
extern std::vector<BuildingConfig> AllBuildings;
extern std::vector<UnitConfig> AllUnits;
extern _SystemConfig SystemConfig;
extern _GameConfig GameConfig;
extern _GameState GameState;

#endif // UNITS_CONFIG_H
