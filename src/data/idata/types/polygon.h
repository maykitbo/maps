#pragma once


namespace maykitbo::maps
{


enum PolygonTypes
{
    P_DEFAULT = -1,
    // buildings:
    P_APARTMENTS,
    P_OFFICE,
    P_SHOP,     
    P_EDUCATION,
    P_MEDICINE,
    P_MANUFACTURE,
    P_DISUSED,
    P_RELIGION,
    P_GOVERMENT,
    P_TRANSPORT,
    P_HOSPITALITY,
    P_CULTURE,
    P_CONSTRUCTION,
    P_PUBLIC,
    P_BANK,
    P_SPORT,
    // areas:
    P_CONSTRUCTION_AREA,
    P_DISUSED_AREA,
    P_WOOD,
    P_PARK,
    P_WATER,
    P_SWIMMING_AREA,
    P_WETLAND,
    P_GRASSLAND
};


} // namespace maykitbo::maps
