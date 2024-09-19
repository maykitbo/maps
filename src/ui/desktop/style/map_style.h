#pragma once


#include <QPen>
#include <unordered_map>

#include "types.h"
#include "polygon_types.h"


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

    const QColor road_color = QColor{155, 128, 32};
    const QColor foot_way_color = QColor{192, 192, 192};
    const QColor cycle_color = QColor{10,   220, 10};
    const std::unordered_map<std::string, QPen> roads =
    {
        {"footway",       {QBrush{       foot_way_color}, 1.4, Qt::DashLine}},
        {"pedestrian",    {QBrush{       foot_way_color}, 1.6, Qt::DashLine}},
        {"service",       {QBrush{QColor{128, 128, 128}}, 1}},
        {"path",          {QBrush{       foot_way_color}, 1,   Qt::DashLine}},
        {"cycleway",      {QBrush{       cycle_color},   1}},
        {"bridleway",     {QBrush{       cycle_color},   1.2}},
        {"steps",         {QBrush{       foot_way_color}, 2}},
        {"unclassified",  {QBrush{QColor{92,  92,  92}},  1.5}},
        {"tertiary",      {QBrush{       road_color},     3}},
        {"tertiary_link", {QBrush{       road_color},     3}},
        {"residential",   {QBrush{       road_color},     2}},
        {"living_street", {QBrush{       road_color},     1.5}},
        {"secondary",     {QBrush{       road_color},     4}},
        {"secondary_link",{QBrush{       road_color},     4}},
        {"primary_link",  {QBrush{       road_color},     5}},
        {"primary",       {QBrush{       road_color},     5}},
        {"construction",  {QBrush{       road_color},     3,   Qt::DashLine}},
        {"proposed",      {QBrush{       road_color},     3,   Qt::DashLine}},
        {"track",         {QBrush{       road_color},     2}},
    };

    const QBrush apartments_brush   {QColor{255, 218, 185}};
    const QBrush office_brush       {QColor{255, 255, 30}};
    const QBrush shop_brush         {QColor{200, 200, 200}};
    const QBrush edu_brush          {QColor{255, 228, 181}};
    const QBrush medicine_brush     {QColor{255, 133, 133}};
    const QBrush manufacture_brush  {QColor{156, 156, 156}};
    const QBrush disused_brush      {QColor{102, 102, 0}};
    const QBrush religion_brush     {QColor{200, 25,  222}};
    const QBrush yes_brush          {QColor{128, 128, 0}};
    const QBrush transport_brush    {QColor{125, 225, 75}};

    const std::unordered_map<PolygonTypes, QBrush> polygons = {
        {APARTMENTS,        {QColor{255, 230, 150}}}, // Light yellow
        {OFFICE,            {QColor{255, 255, 30}}},  // Bright yellow
        {SHOP,              {QColor{240, 180, 100}}}, // Warm orange
        {EDUCATION,         {QColor{120, 220, 120}}}, // Pastel green  
        {MEDICINE,          {QColor{250, 80, 80}}},   // Soft red
        {MANUFACTURE,       {QColor{160, 160, 160}}}, // Medium gray
        {DISUSED,           {QColor{140, 140, 140}}}, // Dark gray
        {RELIGION,          {QColor{200, 150, 200}}}, // Pale purple
        {GOVERMENT,         {QColor{100, 150, 200}}}, // Blue-gray
        {TRANSPORT,         {QColor{50, 50, 50}}},    // Very dark gray
        {HOSPITALITY,       {QColor{220, 190, 130}}}, // Beige
        {CULTURE,           {QColor{180, 100, 180}}}, // Lavender
        {CONSTRUCTION,      {QColor{200, 100, 50}}},  // Burnt orange
        {PUBLIC,            {QColor{150, 200, 150}}}, // Mint green
        {BANK,              {QColor{200, 200, 100}}}, // Light gold
        {SPORT,             {QColor{100, 200, 200}}}, // Pale cyan
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


    const brush_map areas =
    {
        {"construction",        manufacture_area},
        {"disused",             disused_area},
        {"wood",                wood_area},
        {"park",                park_area},
        {"water",               water_area},
        {"swimming_area",       water_area}, // TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!
        {"beach_resort",        beach_area},
        {"wetland",             swamp_area},
        {"grassland",           grass_area},
    };
};



} // namespace maykitbo::maps