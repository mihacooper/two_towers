#include "config.h"

cocos2d::Size ScreenResolution(768, 1024);

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
    }
};

