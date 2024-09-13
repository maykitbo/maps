#include "idata.h"

#include <unordered_set>
#include <fstream>
#include "geojson_handler/polygon_types.h"

using namespace maykitbo::maps;


std::pair<
    std::unordered_map<std::string, int>,
    std::unordered_map<std::string, int>
> readPolygonMapping()
{
    std::unordered_map<std::string, int> mapping;
    std::unordered_map<std::string, int> types;
    std::ifstream file("src/data/buildings.ntoc");
    if (!file)
    {
        std::cout << "File is not open\n";
        return {};
    }

    file.ignore(1024, '\n');
    int val = 0;
    std::string word{};
    while (file && file.peek() != '#')
    {
        file >> val >> word;
        types[word] = val;
        file.ignore(1024, '\n');
    }
    file.ignore(1024, '\n');
    while (file)
    {
        std::string name{};
        word = "";
        while (file && file.peek() != '\n')
        {
            name += word;
            if (word.size() != 0)
                name += ' ';
            file >> word;
        }
        if (name.size() > 0)
        {
            name.resize(name.size() - 1);
            mapping[name] = types[word];
        }
        file.ignore(1024, '\n');
        if (file.peek() == '#')
            file.ignore(1024, '\n');
    }
    return std::make_pair(std::move(types), std::move(mapping));
}


// ALTER TABLE planet_osm_polygon
// ADD COLUMN draw_type INTEGER NOT NULL DEFAULT -1;

int main()
{
    // auto polygin_mapping = readPolygonMapping();
    // std::unordered_map<std::string, int> mapping =
    //     std::move(polygin_mapping.second);
    // std::unordered_map<std::string, int> types =
    //     std::move(polygin_mapping.first);


    // for (auto w : types)
    // {
    //     std::cout << w.first << " | " << w.second << '\n';
    // }
    // std::cout << "_____\n\n";
    // for (auto w : mapping)
    // {
    //     std::cout << w.first << " | " << w.second << '\n';
    // }
    

    // IData db;
    // pqxx::connection c(Conf::postgis);
    // pqxx::work w(c);

    // pqxx::result r = w.exec(
    //     "SELECT osm_id, building FROM planet_osm_polygon WHERE building IS NOT NULL");
    // w.commit();

    // // Prepare update statement
    // c.prepare("update_draw_type", 
    //     "UPDATE planet_osm_polygon SET draw_type = $1 WHERE osm_id = $2");

    // // Vector to store updates
    // std::vector<std::pair<int, int>> updates;

    // // Process each row
    // for (const auto& row : r)
    // {
    //     int id = row["osm_id"].as<int>();
    //     std::string building = row["building"].as<std::string>();


    //     // Check if building type exists in mapping
    //     if (mapping.find(building) != mapping.end())
    //     {
    //         int drawType = mapping[building];
    //         updates.push_back(std::make_pair(drawType, id));
    //     }
    // }

    // std::cout << "updates size = " << updates.size() << '\n';
    // long long k = 0;
    // const long long batch = 50000;
    // // Perform batch update
    // for (const auto& update : updates)
    // {
    //     if ((++k) % batch == 0)
    //     {
    //         std::cout << k << '/' << updates.size() << '\n';
    //     }
    //     w.exec_prepared("update_draw_type", update.first, update.second);
    // }

    // w.commit();

    // std::cout << "Updated " << updates.size() << " rows." << std::endl;

    // return 0;



    IData db;

    // // auto R = db.fetchPolygons(bbox_s{55.816, 55.81, 37.667, 37.655});
    // auto r = db.getConnector().executeNonTransactionalQuery(
    //     "SELECT building, draw_type FROM planet_osm_polygon WHERE building IS NOT NULL LIMIT 1000"
    // );
    // std::cout << r.size() << "\n\n";

    auto r = db.fetchPolygonDraw(bbox_s{55.816, 55.81, 37.667, 37.655}, d_area_s{0, 10000});
    std::cout << r.size() << '\n';
    for (auto i : r)
    {
        std::cout << i[0].c_str() << " | ";
        std::cout << i[1].c_str() << " | ";
        std::cout << i[2].c_str() << "\n";
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


