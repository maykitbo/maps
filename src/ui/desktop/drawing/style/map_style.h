#pragma once


#include <QPen>
#include <unordered_map>

#include "types.h"
#include "idata/types/polygon.h"
#include "idata/types/line.h"


namespace maykitbo::maps
{


struct MapStyle
{
    using brush_map = std::unordered_map<std::string, const QBrush&>;

    static const int hover_highlight = 180;

    const bbox_s init_bbox
        {55.816, 55.809, 37.667, 37.645};

    const int init_width = 900;
    const int point_r = 7;
    const coord_t move_procent = 0.3;
    const coord_t scroll_procent = 0.3;

    // Updated colors suitable for a dark background with improved visibility and aesthetics
    const QColor road_color_main        {230, 215, 0};     // Bright gold for main roads
    const QColor road_color_secondary   {230, 165, 0};     // Orange for secondary roads
    const QColor foot_way_color         {230, 105, 180};   // Hot pink for footways
    const QColor cycleway_color         {50, 205, 50};     // Lime green for cycleways
    const QColor construction_color     {230, 69, 0};      // Bright red-orange for construction
    const QColor abandoned_color        {128, 128, 128};   // Gray for abandoned ways
    const QColor rail_color             {173, 216, 230};   // Light blue for railways
    const QColor platform_color         {32, 178, 170};    // Light sea green for platforms
    const QColor ferry_color            {30, 144, 255};    // Dodger blue for ferry routes
    const QColor subway_color           {255, 0, 255};     // Magenta for subways

    const QPen   basic_road{QBrush{Qt::white}, 3};
    const QBrush basic_point{{255, 215, 0}};  // Gold for points of interest

    // Line styles for different types of ways
    const std::unordered_map<LineTypes, QPen> lines =
    {
        {L_UNKNOWN,                    {{QColor{255, 0, 0, 30}},   0.3, Qt::SolidLine}},

        {L_ABANDONED,                  {{abandoned_color},         1.0, Qt::DashDotLine}},
        {L_UNKNOWN_PATH,               {{abandoned_color},         1.0, Qt::DashDotLine}},
        {L_CONSTRUCTION,               {{construction_color},      2.0, Qt::DashLine}},
        {L_PATH,                       {{foot_way_color},          1.5, Qt::DotLine}},
        {L_STEPS,                      {{foot_way_color},          1.8, Qt::DashDotDotLine}},
        {L_SERVICE,                    {{road_color_secondary},    2.0, Qt::SolidLine}},
        {L_TRANSPORT,                  {{road_color_secondary},    2.0, Qt::SolidLine}},

        {L_CONSTRUCTION_RAIL,          {{construction_color},      2.0, Qt::DashDotLine}},
        {L_SERVICE_RAYL_TRANSPORT,     {{rail_color},              2.2, Qt::SolidLine}},
        {L_PLATFORM_RAYL_TRANSPORT,    {{platform_color},          2.0, Qt::SolidLine}},
        {L_PLATFORM_TRAM_TRANSPORT,    {{platform_color},          2.0, Qt::SolidLine}},
        {L_FERRY_TRANSPORT,            {{ferry_color},             2.5, Qt::SolidLine}},
        {L_TRAM_TRANSPORT,             {{rail_color},              2.0, Qt::SolidLine}},
        {L_FUNICULAR_TRANSPORT,        {{rail_color},              2.0, Qt::SolidLine}},
        {L_LIGHT_RAIL_TRANSPORT,       {{rail_color},              2.5, Qt::SolidLine}},
        {L_SUBWAY_TRANSPORT,           {{subway_color},            2.5, Qt::SolidLine}},
        {L_RAIL_TRANSPORT,             {{rail_color},              3.0, Qt::SolidLine}},

        {L_CYCLEWAY,                   {{cycleway_color},          2.0, Qt::SolidLine}},
        {L_TRACK,                      {{road_color_secondary},    2.5, Qt::SolidLine}},
        {L_RESIDENTIAL,                {{road_color_secondary},    2.8, Qt::SolidLine}},
        {L_TERTIARY,                   {{road_color_main},         3.2, Qt::SolidLine}},
        {L_SECONDARY,                  {{road_color_main},         3.8, Qt::SolidLine}},
        {L_PRIMARY,                    {{road_color_main},         4.6, Qt::SolidLine}},
        {L_TRUNK,                      {{road_color_main},         5.4, Qt::SolidLine}},
        {L_MOTORWAY,                   {{road_color_main},         6.0, Qt::SolidLine}}
    };

    // Define colors for different types of areas/buildings
    const std::unordered_map<PolygonTypes, QBrush> polygons =
    {
        {P_UNKNOWN,           {{255, 0, 0, 30}}},

        // Buildings
        {P_APARTMENTS,        {{70, 130, 180}}},  // Steel blue
        {P_OFFICE,            {{65, 105, 225}}},  // Royal blue
        {P_SHOP,              {{255, 140, 0}}},   // Dark orange
        {P_EDUCATION,         {{60, 179, 113}}},  // Medium sea green
        {P_MEDICINE,          {{220, 20, 60}}},   // Crimson
        {P_MANUFACTURE,       {{112, 128, 144}}}, // Slate gray
        {P_DISUSED,           {{169, 169, 169}}}, // Dark gray
        {P_RELIGION,          {{138, 43, 226}}},  // Blue violet
        {P_GOVERNMENT,        {{47, 79, 79}}},    // Dark slate gray
        {P_TRANSPORT,         {{105, 105, 105}}}, // Dim gray
        {P_HOSPITALITY,       {{210, 180, 140}}}, // Tan
        {P_CULTURE,           {{216, 191, 216}}}, // Thistle
        {P_CONSTRUCTION,      {{205, 133, 63}}},  // Peru
        {P_PUBLIC,            {{46, 139, 87}}},   // Sea green
        {P_BANK,              {{189, 183, 107}}}, // Dark khaki
        {P_SPORT,             {{127, 255, 0}}},   // Chartreuse

        // Natural
        {P_NATURAL_WOOD,      {{34, 139, 34}}},   // Forest green
        {P_NATURAL_GRASSLAND, {{50, 205, 50}}},   // Lime green
        {P_NATURAL_WATER,     {{0, 191, 255}}},   // Deep sky blue
        {P_NATURAL_WETLAND,   {{32, 178, 170}}},  // Light sea green
        {P_NATURAL_ROCK,      {{128, 128, 128}}}, // Gray
        {P_NATURAL_SAND,      {{244, 164, 96}}},  // Sandy brown
        {P_NATURAL_ICE,       {{173, 216, 230}}}, // Light blue
        {P_NATURAL_LANDFORM,  {{205, 133, 63}}},  // Peru
        {P_NATURAL_ANIMAL,    {{160, 82, 45}}},   // Sienna
        {P_NATURAL_BUSH,      {{46, 139, 87}}},   // Sea green
        {P_NATURAL_HANDMADE,  {{160, 160, 160}}}  // Light gray
    };



    const QBrush manufacture_area  {QColor{156, 156, 156, 128}};
    const QBrush disused_area      {QColor{102, 102, 0,   128}};
    const QBrush wood_area         {QColor{34, 139, 34,   128}};
    const QBrush park_area         {QColor{60,179,113,   128}};
    const QBrush scrub_area        {QColor{0,100,0,   128}};
    const QBrush water_area        {QColor{28,163,236,   255}};
    const QBrush beach_area        {QColor{236,204,162, 255}};
    const QBrush swamp_area        {QColor{84,98,26, 255}};
    const QBrush grass_area        {QColor{65,152,10, 255}};
    // const QBrush swimming_area     {}

};



} // namespace maykitbo::maps