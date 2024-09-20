#pragma once


#include "types/line.h"
#include "types/polygon.h"
#include "features/set.h"
#include "postgis_connector.h"
// #inc


namespace maykitbo::maps
{


class IData
{
    public:
        IData(const std::string& conn_str);

        template<class way_conteiner, class coords_preprocess>
        FeatureSet<way_conteiner, coords_preprocess, PolygonTypes>
        fethPolygons(const bbox_s& bbox, const d_area_s& darea, int limit = 10000);

        template<class way_conteiner, class coords_preprocess>
        FeatureSet<way_conteiner, coords_preprocess, LineTypes>
            fethLines(const bbox_s& bbox, int min_draw_type, int limit = 10000);
    
    private:
        PostGISConnector pgc_;
};


IData::IData(const std::string& conn_str)
    : pgc_(conn_str) {}


template<class way_conteiner, class coords_preprocess>
FeatureSet<way_conteiner, coords_preprocess, PolygonTypes>
IData::fethPolygons(const bbox_s& bbox, const d_area_s& darea, int limit)
{
    pqxx::result R = pgc_.fetchBboxDarea(
        DBStruct::POLYGON_TABLE, bbox, darea, limit);
    
    FeatureSet<way_conteiner, coords_preprocess, PolygonTypes> polygons;
    polygons.parse(R);
    return polygons;
}


template<class way_conteiner, class coords_preprocess>
FeatureSet<way_conteiner, coords_preprocess, LineTypes>
IData::fethLines(const bbox_s& bbox, int min_draw_type, int limit)
{
    pqxx::result R = pgc_.fetchBboxMinDrawType(
        DBStruct::LINE_TABLE, bbox, min_draw_type, limit);
    
    FeatureSet<way_conteiner, coords_preprocess, LineTypes> polygons;
    polygons.parse(R);
    return polygons;
}


} // namespace maykitbo::maps