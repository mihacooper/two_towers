#include "config.h"

cocos2d::Size ScreenResolution(768, 1024);

std::vector<UnitConfig> AllUnits =
{
    UnitConfig
    {
        "SampleUnit",
        "unit.png",
    },
};

const BuildingConfig SampleBuilding =
{
    // name
    "SampleBuilding",
    // image
    "building.png",
    // help
    "Help message",
    // level
    0,
    // each level config
    {
        {
            // image
            "building.png",
            // help
            "Help message",
            // objects
            {
                "SampleUnit",
                "SampleUnit",
            },
        },
        {
            // image
            "building.png",
            // help
            "Help message",
            // objects
            {
                "SampleUnit",
            },
        },
        {
            // image
            "building.png",
            // help
            "Help message",
            // objects
            {
                "SampleUnit",
            },
        },
    }
};

std::vector<BuildingConfig> AllBuildings =
{
    // default building
    {
        // name
        "SampleBuilding",
        // image
        "building.png",
        // help
        "Help message",
        // level
        0,
        // each level config
        {
            {
                // image
                "building.png",
                // help
                "Help message",
                // objects
                {},
            },
            {
                // image
                "building.png",
                // help
                "Help message",
                // objects
                {},
            },
            {
                // image
                "building.png",
                // help
                "Help message",
                // objects
                {},
            },
        }
    },
    SampleBuilding,
    SampleBuilding,
    SampleBuilding,
    SampleBuilding,
    SampleBuilding,
    SampleBuilding,
    SampleBuilding,
    SampleBuilding,
    SampleBuilding,
    SampleBuilding,
    SampleBuilding,
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
        {384, 50},
        {250, 100}, {200, 210}, {250, 320},
        {518, 100}, {568, 210}, {518, 320},
    },
    // Rect bfld_choice_area =
    { 284, 824, 484, 1024 },
};

_GameConfig GameConfig =
{
    // unsigned int initial_tower_life =
    20U,
    // unsigned int initial_wall_life =
    20U,
};

_GameState GameState =
{
    // PlayerConfig first_player =
    {
        //unsigned int tower_life =
        GameConfig.initial_tower_life,
        //unsigned int wall_life =
        GameConfig.initial_wall_life,
        // vector<BuildingConfig> buildings =
        { AllBuildings[0] },
    },
    //PlayerConfig second_player;
    {
        //unsigned int tower_life =
        GameConfig.initial_tower_life,
        //unsigned int wall_life =
        GameConfig.initial_wall_life,
        // vector<BuildingConfig> buildings =
        { AllBuildings[0] },
    },
};

