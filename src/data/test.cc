#include "idata.h"


using namespace maykitbo::maps;

    // bboxes = [
    // #   south    west    north   east
    //     (55.810, 37.660, 55.812, 37.666),
    //     (55.809, 37.655, 55.813, 37.666),
    //     (55.809, 37.650, 55.814, 37.666),
    //     (55.805, 37.650, 55.814, 37.666),
    //     (55.800, 37.645, 55.812, 37.666)
    // ]

int main()
{



    // std::string A = "0101000020110F000031DF50D7674657412E8E4F9F4C065241";
    // std::cout << A.size() << '\n';
    // for (int k = 0; k < A.size(); ++k) {
    //     std::cout << A[k];
    //     if (k == (A.size() / 2 - 1)) {
    //         std::cout << '\n';
    //     }
    // }
    // std::cout << '\n';

    // return 0;

    IData db;

    // db().listTables();
    // db.listColumns("geography_columns");
    // db.listColumns("geometry_columns");
    // db.listColumns("spatial_ref_sys");
    // db.listColumns("planet_osm_point");
    // db.listColumns("osm2pgsql_properties");
    // db.listColumns("ways_vertices_pgr");
    // db.listColumns("ways");
    // db.listColumns("planet_osm_line");
    // db.listColumns("pointsofinterest");
    // db.listColumns("configuration");
    // db().listColumns("planet_osm_polygon");
    // db.listColumns("planet_osm_roads");
    // return 0;


    // std::cout << "\nFetch Initial BBOX:\n";
    // db.fetchInitialData("planet_osm_roads", 5);

    std::cout << "\nFetch BBOX:\n";
    // auto R = db.fetchGeoJSONByBBOX("planet_osm_roads", 36.14, 40.99, 56.27, 56.49);
    auto R = db.fetchPolygons(bbox_s{55.816, 55.81, 37.667, 37.655});

    // R.features([&] (const GeoJson::Feature& feature) {
    //     feature.geomWay([&] (point_s p) {
    //         // std::cout << p.lat << '\t' << p.lon << '\n';
    //     });
    // });

    const GeoJson::data_t& g = R.getJsonData();
    std::cout << g["properties"] << '\n';

    
    // std::cout << "R.size() = " << R.size() << '\t';
    // std::cout << "R[0].size = " << R[0].size() << '\n';

    return 0;
}   


