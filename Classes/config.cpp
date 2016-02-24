#include "config.h"

cocos2d::Size ScreenResolution(768, 1024);

std::vector<UnitConfig> AllUnits =
{
    UnitConfig{"building.png"},
};

std::vector<BuildingConfig> AllBuildings =
{
    BuildingConfig{"building.png", "", ""},
    BuildingConfig{"building.png", "", ""},
    BuildingConfig{"building.png", "", ""},
    BuildingConfig{"building.png", "", ""},
    BuildingConfig{"building.png", "", ""},
    BuildingConfig{"building.png", "", ""},
    BuildingConfig{"building.png", "", ""},
    BuildingConfig{"building.png", "", ""},
    BuildingConfig{"building.png", "", ""},
    BuildingConfig{"building.png", "", ""},
    BuildingConfig{"building.png", "", ""},
    BuildingConfig{"building.png", "", ""},
};

_SystemConfig SystemConfig =
{
    /*
     *  choice scene
     */
    // Vec2 slct_main_label =
    {512, 668},
    // Rect slct_choice_area =
    {0, 0, 768, 200},
    // vector<Vec2> slct_curr_buildings =
    {
        {214, 824}, {324, 824}, {434, 824}, {544, 824},
        {214, 714}, {324, 714}, {434, 714}, {544, 714},
        {214, 604}, {324, 604}, {434, 604}, {544, 604},
    },
    // vector<Vec2> slct_selected_buildings =
    {
        {104, 100}, {214, 100}, {324, 100}, {434, 100}, {544, 100}, {654, 100}
    },

    /*
     *  game scene
     */
    // vector<Vec2> bfld_units =
    {
        {75, 882}, {75, 772}, {75, 662}, {75, 552}, {75, 442}, {75, 332},
        {693, 882}, {693, 772}, {693, 662}, {693, 552}, {693, 442}, {693, 332}
    },
    // vector<Vec2> bfld_buildings =
    {
        {300, 100}, {200, 210}, {250, 320},
        {468, 100}, {568, 210}, {518, 320},
    },
};

_GameConfig GameConfig = {20U};

_GameState GameState =
{
    // vector<Sprite*> fp_buildings =
    {},
    // unsigned int fp_tower =
    GameConfig.tower_life,

    // vector<Sprite*> sp_buildings =
    {},
    // unsigned int sp_tower =
    GameConfig.tower_life,
};

