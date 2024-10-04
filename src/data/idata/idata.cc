#include "idata.h"


using namespace maykitbo::maps;



IData::IData(const std::string& conn_str)
    : pgc_(conn_str)
{}


const db::Connector& IData::connector()
{
    return pgc_;
}


std::string IData::infoAsString(const std::string& table, idx_t id) const
{
    pqxx::result R = pgc_.getInfoById(table, id);
    std::string info;
    for (const auto& r : R[0])
    {
        if (!r.is_null())
        {
            info += std::string(r.name()) + " = " + r.c_str() + "\n";
        }
    }
    return info;
}


std::string IData::pointInfoAsString(idx_t id) const
{
    return infoAsString(DBDT::POINT_TABLE, id);
}


std::string IData::polygonInfoAsString(idx_t id) const
{
    return infoAsString(DBDT::POLYGON_TABLE, id);
}


std::string IData::lineInfoAsString(idx_t id) const
{
    return infoAsString(DBDT::LINE_TABLE, id);
}

std::string IData::roadInfoAsString(idx_t id) const
{
    return infoAsString(DBDT::ROAD_TABLE, id);
}


void IData::route(idx_t id_1, idx_t id_2) const
{
    pqxx::result R = pgc_.createRoute(DBDT::POINT_TABLE, id_1, id_2);
    std::cout << "ROUTE START\n";

    std::cout << "\tsize = " << R.size() << '\n';

    std::cout << "ROUTE END\n";
}


// void IData::bboxSeparation(int depth, const bbox_s& bbox, std::function<void(const bbox_s&)> func)
// {
//     // std::cout << "new bbox " << bbox << "\n";
//     if (depth > 0 && GCS::area(bbox) > max_poly_bbox)
//     {
//         coord_t mean_lat = bbox.min_lat + (bbox.max_lat - bbox.min_lat) / 2.0;
//         coord_t mean_lon = bbox.min_lon + (bbox.max_lon - bbox.min_lon) / 2.0;
//         bboxSeparation(depth - 1, {bbox.max_lat, mean_lat, bbox.max_lon, mean_lon}, func);
//         bboxSeparation(depth - 1, {bbox.max_lat, mean_lat, mean_lon, bbox.min_lon}, func);
//         bboxSeparation(depth - 1, {mean_lat, bbox.min_lat, bbox.max_lon, mean_lon}, func);
//         bboxSeparation(depth - 1, {mean_lat, bbox.min_lat, mean_lon, bbox.min_lon}, func);
//     }
//     else
//     {
//         func(bbox);
//     }
// }


PolygonSet IData::fetchPolygons(const bbox_s& bbox, const d_area_s& darea, float sparse_tol, limit_t limit)
{
    // PolygonSet set;
    // int num_bboxes = 0;
    // bboxSeparation(3, bbox, [&] (const bbox_s& bb)
    // {
    //     ++num_bboxes;
    //     pqxx::result R = pgc_.fetch
    //     (
    //         DBDT::POLYGON_TABLE,
    //         {
    //             Q::wayColOutSelect(sparse_tol),
    //             Q::columnsSelect({DBDT::DRAW_TYPE_COL, DBDT::ID_COL, DBDT::WAY_AREA_COL})
    //         },
    //         {
    //             Q::bboxWWayCond(bb),
    //             Q::dareaCond(darea),
    //         },
    //         limit
    //     );
    //     set.parse(R);
    // });
    // std::cout << "number of poly bboxes = " << num_bboxes << "\n";
    // return set;
    return fetchHelper<PolygonSet>(
        DBDT::POLYGON_TABLE,
        {
            // Q::wayColOutSelect(sparse_tol),
            Q::wayColOutSelect(),
            Q::columnsSelect({DBDT::DRAW_TYPE_COL, DBDT::ID_COL, DBDT::WAY_AREA_COL})
        },
        {
            Q::bboxWWayCond(bbox),
            Q::dareaCond(darea),
        },
        limit
    );
}


LineSet IData::fetchLines(const bbox_s& bbox, int min_draw_type, limit_t limit)
{
    return fetchHelper<LineSet>(
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


PointSet IData::fetchPoints(const bbox_s& bbox, limit_t limit)
{
    return fetchHelper<PointSet>(
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


RoadSet IData::fetchRoads(const bbox_s& bbox, int min_draw_type, limit_t limit)
{
    return fetchHelper<RoadSet>(
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

