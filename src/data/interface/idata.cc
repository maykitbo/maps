#include "idata.h"


using namespace maykitbo::maps;


IData::IData(const std::string &connect_string)
{
    pgc_.connect(connect_string);
}


OsmData IData::fetch(const std::string& table, const bbox_s& bbox, int srid)
{
    return OsmData(std::move(pgc_.fetchGeoJsonByBBOX(table, bbox, srid))); 
}


OsmData IData::fetchRoads(const bbox_s& bbox, int srid)
{
    return OsmData(std::move(pgc_.fetchGeoJsonByBBOX("planet_osm_roads", bbox, srid)));
}                        


OsmData IData::fetchPoints(const bbox_s& bbox, int srid)
{
    return OsmData(std::move(pgc_.fetchGeoJsonByBBOX("planet_osm_point", bbox, srid)));
}                        


OsmData IData::fetchPolygons(const bbox_s& bbox, int srid)
{
    return OsmData(std::move(pgc_.fetchGeoJsonByBBOX("planet_osm_polygon", bbox, srid)));
}                            


void IData::listColumns(const std::string& table)
{
    pgc_.listColumns(table);
}


void IData::listTables()
{
    pgc_.listTables();
}

