#pragma once


#include "types/line.h"
#include "types/polygon.h"
#include "features/set.h"
#include "connector.h"

#include "time_test.h"


#include <unordered_map>
#include <list>
#include <functional>


namespace maykitbo::maps
{


class IData
{
    using DBDT = db::DBStruct;
    using Q = db::Query;

    public:
        using limit_t = unsigned long long;

        using coordinates_t = std::vector<point_s>;

        IData(const std::string& conn_str);

        // 1.0 >= sparse tol >= 0.0

        PolygonSet fetchPolygons(const bbox_s& bbox, const d_area_s& darea, float sparse_tol, limit_t limit = 100000);
        LineSet fetchLines(const bbox_s& bbox, int min_draw_type, limit_t limit = 100000);
        PointSet fetchPoints(const bbox_s& bbox, limit_t limit = 100000);
        RoadSet fetchRoads(const bbox_s& bbox, int min_draw_type, limit_t limit = 100000);

        const db::Connector& connector();
        
        std::string infoAsString(const std::string& table, idx_t id) const;
        std::string polygonInfoAsString(idx_t id) const;
        std::string pointInfoAsString(idx_t id) const;
        std::string lineInfoAsString(idx_t id) const;
        std::string roadInfoAsString(idx_t id) const;

        void route(idx_t id_1, idx_t id_2) const;

    private:
        db::Connector pgc_;

        // const coord_t max_poly_bbox = 2e8;
        // void bboxSeparation(int depth, const bbox_s& bbox, std::function<void(const bbox_s&)> func);

        bbox_s bbox_;

        // template<class Way, class CPrep, class return_type>
        template<class Set>
        Set fetchHelper(const std::string& table,
                        const Q::set_sw_t& s,
                        const Q::set_sw_t& w,
                        limit_t limit);
 

};


// std::string IData::polygonInfoAsString(idx_t id) const
// {

// }

template<class Set>
// template<class Way, class CPrep, class return_type>
Set IData::fetchHelper( const std::string& table,
                        const Q::set_sw_t& s,
                        const Q::set_sw_t& w,
                        limit_t limit)
{
    // std::cout << "Idata::fetch start " << table << "\n";

    // TimeTest fetch_time("Fetch in idata " + table);
    pqxx::result R = pgc_.fetch(table, s, w, limit);
    // fetch_time.pause();
    
    TimeTest parse_time("Parse in idata"  + table);
    Set set;
    set.parse(R);
    parse_time.pause();

    // std::cout << fetch_time << parse_time;

    // std::cout << "Idata::fetch done " << table << "\n";

    return set;
}



} // namespace maykitbo::maps