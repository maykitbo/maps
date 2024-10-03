#pragma once


#include "types/line.h"
#include "types/polygon.h"
#include "features/set.h"
#include "connector.h"

#include "time_test.h"


#include <unordered_map>
#include <list>


namespace maykitbo::maps
{


class IData
{
    using DBDT = db::DBStruct;
    using Q = db::Query;

    public:
        using limit_t = unsigned long long;

        IData(const std::string& conn_str);

        // 1.0 >= sparse tol >= 0.0
        template<class Way, class CPrep>
        DrawFeatureSet<Way, CPrep, PolygonTypes>
        fetchPolygons(const bbox_s& bbox, const d_area_s& darea, float sparse_tol, limit_t limit = 10000) const;

        template<class Way, class CPrep>
        DrawFeatureSet<Way, CPrep, LineTypes>
        fetchLines(const bbox_s& bbox, int min_draw_type, limit_t limit = 10000) const;

        template<class Way, class CPrep>
        FeatureSet<Way, CPrep>
        fetchPoints(const bbox_s& bbox, limit_t limit = 10000) const;

        template<class Way, class CPrep>
        DrawFeatureSet<Way, CPrep, LineTypes>
        fetchRoads(const bbox_s& bbox, int min_draw_type, limit_t limit = 10000) const;

        const db::Connector& connector();
        
        std::string infoAsString(const std::string& table, idx_t id) const;
        std::string polygonInfoAsString(idx_t id) const;
        std::string pointInfoAsString(idx_t id) const;
        std::string lineInfoAsString(idx_t id) const;
        std::string roadInfoAsString(idx_t id) const;

        void route(idx_t id_1, idx_t id_2) const;

    private:
        db::Connector pgc_;


        template<class Way, class CPrep, class return_type>
        return_type fetchHelper(const std::string& table,
                                const Q::set_sw_t& s,
                                const Q::set_sw_t& w,
                                limit_t limit) const;
 

};


// std::string IData::polygonInfoAsString(idx_t id) const
// {

// }


template<class Way, class CPrep, class return_type>
return_type IData::fetchHelper(const std::string& table,
                               const Q::set_sw_t& s,
                               const Q::set_sw_t& w,
                               limit_t limit) const
{
    std::cout << "Idata::fetch start " << table << "\n";

    TimeTest fetch_time("Fetch in idata " + table);
    pqxx::result R = pgc_.fetch(table, s, w, limit);
    fetch_time.pause();
    
    TimeTest parse_time("Parse in idata"  + table);
    return_type set;
    set.parse(R);
    parse_time.pause();

    std::cout << fetch_time << parse_time;

    std::cout << "Idata::fetch done " << table << "\n";

    return set;
}


template<class Way, class CPrep>
DrawFeatureSet<Way, CPrep, PolygonTypes>
IData::fetchPolygons(const bbox_s& bbox, const d_area_s& darea, float sparse_tol, limit_t limit) const
{
    return fetchHelper<Way, CPrep, DrawFeatureSet<Way, CPrep, PolygonTypes>>(
        DBDT::POLYGON_TABLE,
        {
            Q::wayColOutSelect(sparse_tol),
            Q::columnsSelect({DBDT::DRAW_TYPE_COL, DBDT::ID_COL})
        },
        {
            Q::dareaCond(darea),
            Q::bboxWWayCond(bbox)
        },
        limit
    );
}


template<class Way, class CPrep>
DrawFeatureSet<Way, CPrep, LineTypes>
IData::fetchLines(const bbox_s& bbox, int min_draw_type, limit_t limit) const
{
    return fetchHelper<Way, CPrep, DrawFeatureSet<Way, CPrep, LineTypes>>(
        DBDT::LINE_TABLE,
        {
            Q::wayColOutSelect(),
            Q::columnsSelect({DBDT::DRAW_TYPE_COL, DBDT::ID_COL})
        },
        {
            Q::minDrawTypeCond(min_draw_type),
            Q::bboxWWayCond(bbox)
        },
        limit
    );
}


template<class Way, class CPrep>
FeatureSet<Way, CPrep>
IData::fetchPoints(const bbox_s& bbox, limit_t limit) const
{
    return fetchHelper<Way, CPrep, FeatureSet<Way, CPrep>>(
        DBDT::POINT_TABLE,
        {
            Q::wayColOutSelect(),
            Q::columnsSelect({DBDT::ID_COL})
        },
        {
            Q::bboxWWayCond(bbox)
        },
        limit
    );
}


template<class Way, class CPrep>
DrawFeatureSet<Way, CPrep, LineTypes>
IData::fetchRoads(const bbox_s& bbox, int min_draw_type, limit_t limit) const
{
    return fetchHelper<Way, CPrep, DrawFeatureSet<Way, CPrep, LineTypes>>(
        DBDT::ROAD_TABLE,
        {
            Q::wayColOutSelect(),
            Q::columnsSelect({DBDT::DRAW_TYPE_COL, DBDT::ID_COL})
        },
        {
            Q::minDrawTypeCond(min_draw_type),
            Q::bboxWWayCond(bbox)
        },
        limit
    );
}


} // namespace maykitbo::maps