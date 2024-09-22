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

    const bbox_s init_bbox
        {55.816, 55.809, 37.667, 37.645};

    const int init_width = 900;
    // const QBrush apartments{QColor{255, 218, 185}};
    // const QBrush buildings{QColor{189, 183, 107}};
    // const QPen basic_polygon{QBrush{Qt::magenta}, 2};
    const QPen basic_road{QBrush{Qt::white}, 3};
    // const QPen basic_line{QBrush{Qt::green}, 2};
    const coord_t move_procent = 0.3;
    const coord_t scroll_procent = 0.3;

    // Define colors suitable for a dark background with the requested adjustments
    const QColor road_color_main = QColor{170, 170, 100};       // Light yellowish-gray for main roads
    const QColor road_color_secondary = QColor{140, 140, 80};   // Medium yellowish-gray for secondary roads
    const QColor foot_way_color = QColor{120, 60, 120};        // Light magenta for footways
    const QColor cycleway_color = QColor{20, 200, 20};        // Brighter green for cycleways
    const QColor construction_color = QColor{80, 80,  80};    // Muted orange for construction (unchanged)
    const QColor abandoned_color = QColor{255, 0,  0};

    // Line styles for different types of ways
    const std::unordered_map<LineTypes, QPen> lines =
    {
        {L_ABANDONED,         {QBrush{abandoned_color},         0.8, Qt::DashDotLine}},
        {L_UNKNOWN_PATH,      {QBrush{abandoned_color},         0.8, Qt::DashDotLine}},
        {L_CONSTRUCTION,      {QBrush{construction_color},      2.0, Qt::DashLine}},
        {L_PATH,              {QBrush{foot_way_color},          1.5, Qt::DashLine}},
        {L_STEPS,             {QBrush{foot_way_color},          2.0, Qt::DotLine}},
        {L_SERVICE,           {QBrush{road_color_secondary},    1.5, Qt::SolidLine}},
        {L_TRANSPORT,         {QBrush{road_color_secondary},    1.5, Qt::SolidLine}},
        {L_CYCLEWAY,          {QBrush{cycleway_color},          2.0, Qt::SolidLine}},
        {L_TRACK,             {QBrush{road_color_secondary},    2.5, Qt::SolidLine}},
        {L_RESIDENTIAL,       {QBrush{road_color_secondary},    2.8, Qt::SolidLine}},
        {L_TERTIARY,          {QBrush{road_color_main},         3.2, Qt::SolidLine}},
        {L_SECONDARY,         {QBrush{road_color_main},         3.8, Qt::SolidLine}},
        {L_PRIMARY,           {QBrush{road_color_main},         4.6, Qt::SolidLine}},
        {L_TRUNK,             {QBrush{road_color_main},         5.4, Qt::SolidLine}},
        {L_MOTORWAY,          {QBrush{road_color_main},         5.6, Qt::SolidLine}}
    };

    // Define colors for different types of areas/buildings
    const std::unordered_map<PolygonTypes, QBrush> polygons =
    {
        // buildings
        {P_APARTMENTS,        {QColor{90,  110, 140}}},  // Muted blue-gray
        {P_OFFICE,            {QColor{80,  100, 130}}},  // Muted steel blue
        {P_SHOP,              {QColor{130, 100, 80 }}},  // Muted brown-orange
        {P_EDUCATION,         {QColor{100, 130, 100}}},  // Muted green
        {P_MEDICINE,          {QColor{130, 80,  80 }}},  // Muted red
        {P_MANUFACTURE,       {QColor{110, 110, 110}}},  // Medium gray
        {P_DISUSED,           {QColor{80,  80,  80 }}},  // Dark gray
        {P_RELIGION,          {QColor{110, 90,  130}}},  // Muted purple
        {P_GOVERNMENT,        {QColor{90,  110, 130}}},  // Muted teal
        {P_TRANSPORT,         {QColor{60,  60,  60 }}},  // Very dark gray
        {P_HOSPITALITY,       {QColor{120, 110, 90 }}},  // Muted beige
        {P_CULTURE,           {QColor{100, 80,  110}}},  // Muted lavender
        {P_CONSTRUCTION,      {QColor{140, 100, 70 }}},  // Muted brown
        {P_PUBLIC,            {QColor{100, 130, 100}}},  // Muted green (same as education)
        {P_BANK,              {QColor{130, 130, 90 }}},  // Muted olive
        {P_SPORT,             {QColor{80,  130, 130}}},  // Muted cyan

        // Natural
        {P_NATURAL_WOOD,      {QColor{30,  100, 30 }}},  // Dark green for forests
        {P_NATURAL_GRASSLAND, {QColor{50,  150, 50 }}},  // Medium green for grasslands
        {P_NATURAL_WATER,     {QColor{30,  60,  120}}},  // Dark blue for water bodies
        {P_NATURAL_WETLAND,   {QColor{40,  80,  60 }}},  // Teal for wetlands
        {P_NATURAL_ROCK,      {QColor{100, 100, 100}}}, // Medium gray for rocky areas
        {P_NATURAL_SAND,      {QColor{140, 120, 80 }}},  // Muted sandy brown
        {P_NATURAL_ICE,       {QColor{160, 200, 220}}},  // Light blue for ice/snow
        {P_NATURAL_LANDFORM,  {QColor{90,  90,  70 }}},  // Dark beige for landforms
        {P_NATURAL_ANIMAL,    {QColor{170, 110, 80 }}},  // Soft brown for animal areas
        {P_NATURAL_BUSH,      {QColor{40,  100, 40 }}},  // Dark green (slightly different) for bushes
        {P_NATURAL_HANDMADE,  {QColor{110, 90,  70 }}}  // Muted brown for handmade natural features
    
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