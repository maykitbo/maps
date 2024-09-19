#include "idata.h"

#include <unordered_set>
#include <fstream>
#include "geojson_handler/polygon_types.h"
#include "draw_polygon_data.h"

using namespace maykitbo::maps;




int main()
{
    IData db;

    // // auto R = db.fetchPolygons(bbox_s{55.816, 55.81, 37.667, 37.655});
    // auto r = db.getConnector().executeNonTransactionalQuery(
    //     "SELECT building, draw_type FROM planet_osm_polygon WHERE building IS NOT NULL LIMIT 1000"
    // );
    // std::cout << r.size() << "\n\n";

    auto r = db.fetchPolygonDraw(bbox_s{55.816, 55.81, 37.667, 37.655}, d_area_s{0, 10000});
    // std::cout << r.size() << '\n';

    // DrawPolygonData<std::vector<point_s>, CoordsPreprocess<point_s>> data;
    // data.fetch(bbox_s{55.816, 55.81, 37.667, 37.655}, d_area_s{0, 10000});
    for (auto i : r)
    {
        // for (auto i : GeoJson::wkbToCoordinates(i[1].as<const char*>()))
        // {
        //     std::cout << "{" << i.first << ", " << i.second << "}, ";
        // }
        std::cout << "\n" <<
            // i[0].c_str() << " | " <<
            i["wkb_way"].c_str() << "\n\n" <<
            i["osm_id"].c_str() << "\n\n" <<
            // i[3].c_str() << "\n\n" <<
            // i[4].c_str() << "\n\n" <<
            "\n";
    }

    // std::unordered_set<std::string> unknown;

    // for (auto i : r)
    // {
    //     if (types.find(i[0].c_str()) == types.end() && types.find(i[1].c_str()) == types.end())
    //     {
    //         unknown.insert(i[1].c_str());
    //         unknown.insert(i[0].c_str());
    //         std::cout << i[0].c_str() << " | ";
    //         std::cout << i[1].c_str() << "\n";
    //     }
    // }
    // std::cout << unknown.size() << '\n';
    // for (auto i : unknown)
    // {
    //     std::cout << i << '\n';
    // }


    // return 0;
}   


