#include "idata.h"


using namespace maykitbo::maps;


IData::IData(const std::string &connect_string)
    : pgc_(connect_string)
{}


GeoJson IData::fetch(const std::string& table, const bbox_s& bbox, d_area_s darea,  int srid) const
{
    return GeoJson(std::move(pgc_.fetchGeoJsonByBBOX(table, bbox, darea, srid))); 
}


GeoJson IData::fetch(const std::string& table, const bbox_s& bbox, int srid) const
{
    return GeoJson(std::move(pgc_.fetchGeoJsonByBBOX(table, bbox, srid))); 
}


GeoJson IData::fetchRoads(const bbox_s& bbox, d_area_s darea, bool cache, int srid) const
{
    return fetch("planet_osm_roads", bbox, darea, srid);
}   

GeoJson IData::fetchLines(const bbox_s& bbox, bool cache, int srid) const
{
    // return GeoJson(std::move(pgc_.fetchGeoJsonByBBOX("planet_osm_line", bbox, srid)));
    return fetch("planet_osm_line", bbox, srid);
}    


GeoJson IData::fetchPoints(const bbox_s& bbox, d_area_s darea, bool cache, int srid) const
{
    // return GeoJson(std::move(pgc_.fetchGeoJsonByBBOX("planet_osm_point", bbox, srid)));
    return fetch("planet_osm_point", bbox, darea, srid);
}                        


GeoJson IData::fetchPolygons(const bbox_s& bbox, d_area_s darea, bool cache, int srid) const
{
    // return GeoJson(std::move(pgc_.fetchGeoJsonByBBOX("planet_osm_polygon", bbox, srid)));
    return fetch("planet_osm_polygon", bbox, darea, srid);
}                            


void IData::listColumns(const std::string& table) const
{
    pgc_.listColumns(table);
}


void IData::listTables() const
{
    pgc_.listTables();
}

