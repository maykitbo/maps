#pragma once


#include <QPen>
#include <unordered_map>

#include "types.h"


namespace maykitbo::maps
{


struct MapStyle
{
    const bbox_s init_bbox
        {55.816, 55.809, 37.667, 37.645};

    const int init_width = 900;
    // const QBrush apartments{QColor{255, 218, 185}};
    // const QBrush buildings{QColor{189, 183, 107}};
    // const QPen basic_polygon{QBrush{Qt::magenta}, 2};
    const QPen basic_road{QBrush{Qt::white}, 3};
    // const QPen basic_line{QBrush{Qt::green}, 2};
    const coord_t move_procent = 0.1;
    const coord_t scroll_procent = 0.1;

    inline static const QColor road_color = QColor{155, 128, 32};
    inline static const std::unordered_map<std::string, QPen> roads =
    {
        {"footway",       {QBrush{QColor{192, 192, 192}}, 1.4, Qt::DashLine}},
        {"service",       {QBrush{QColor{128, 128, 128}}, 1}},
        {"path",          {QBrush{QColor{192, 192, 192}}, 1,   Qt::DashLine}},
        {"cycleway",      {QBrush{QColor{0,   255, 0}},   1}},
        {"tertiary",      {QBrush{       road_color},     3}},
        {"residential",   {QBrush{       road_color},     2}},
        {"steps",         {QBrush{QColor{192, 192, 192}}, 2}},
        {"unclassified",  {QBrush{QColor{92,  92,  92}},  1.5}},
        {"tertiary_link", {QBrush{       road_color},     3}},
        {"construction",  {QBrush{       road_color},     3,   Qt::DashLine}},
    };

    inline static const QBrush apartments_brush  {QColor{255, 218, 185}};
    inline static const QBrush office_brush      {QColor{255, 255, 102}};
    inline static const QBrush shop_brush        {QColor{200, 200, 102}};
    inline static const QBrush edu_brush         {QColor{255, 228, 181}};
    inline static const QBrush medicine_brush    {QColor{255, 133, 133}};
    inline static const QBrush manufacture_brush {QColor{156, 156, 156}};
    inline static const QBrush disused_brush     {QColor{102, 102, 0}};
    inline static const QBrush yes_brush         {QColor{128, 128, 0}};
    inline static const std::unordered_map<std::string, const QBrush&> buildings =
    {
        {"apartments",      apartments_brush},

        {"office",          office_brush},
        {"commercial",      office_brush},

        {"service",         shop_brush},
        {"retail",          shop_brush},
        {"sports_centre",   shop_brush},
        {"toilets",         shop_brush},

        {"kindergarten",    edu_brush},
        {"university",      edu_brush},

        {"clinic",          medicine_brush},

        {"manufacture",     manufacture_brush},
        {"garage",          manufacture_brush},
        {"garages",         manufacture_brush},
        {"roof",            manufacture_brush},

        {"disused",         disused_brush},

        {"yes",             yes_brush}
    };
};



} // namespace maykitbo::maps