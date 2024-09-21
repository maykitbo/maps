#pragma once


#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

#include "config.h"
#include "postgis_connector.h"


// ALTER TABLE planet_osm_polygon
// ADD COLUMN draw_type INTEGER NOT NULL DEFAULT -1;

// ALTER TABLE planet_osm_line
// ADD COLUMN draw_type INTEGER NOT NULL DEFAULT -1;


namespace maykitbo::maps
{


std::pair<
    std::unordered_map<std::string, int>,
    std::unordered_map<std::string, int>
> readPolygonMapping(const std::string& ntoc_path)
{
    std::unordered_map<std::string, int> mapping;
    std::unordered_map<std::string, int> types;
    std::ifstream file(ntoc_path);
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


void realLines(const std::unordered_map<std::string, int>& mapping)
{
    pqxx::connection c(Conf::postgis);
    pqxx::work w(c);


    pqxx::result r = w.exec(
        "SELECT osm_id, highway "
        "FROM planet_osm_line "
        "WHERE highway IS NOT NULL AND highway is distinct from \'no\'");
    w.commit();
    std::cout << "SELECT done. Number of rows = " << r.size() << '\n';


    c.prepare("update_draw_type",
        "UPDATE planet_osm_line SET draw_type = $1 WHERE osm_id = $2"  
    );



    std::vector<std::pair<int, int>> updates;
    for (const auto& row : r)
    {
        int id = row["osm_id"].as<int>();
        std::string highway = row["highway"].as<std::string>();

        if (mapping.find(highway) != mapping.end())
        {
            int drawType = mapping.find(highway)->second;
            updates.push_back(std::make_pair(drawType, id));
        }
        else
        {
            updates.push_back(std::make_pair(1, id));
        }
    }
    std::cout << "PREPARE done. Updates size = " << updates.size() << '\n';


    long long k = 0;
    const long long batch = 50000;
    for (const auto& update : updates)
    {
        if ((++k) % batch == 0)
        {
            std::cout << k << '/' << updates.size() << '\n';
        }
        w.exec_prepared("update_draw_type", update.first, update.second);
    }
    w.commit();


    std::cout << "Updated " << updates.size() << " rows.\n";
}


void realBuildings(const std::unordered_map<std::string, int>& mapping)
{
    pqxx::connection c(Conf::postgis);
    pqxx::work w(c);
    pqxx::result r = w.exec(
        "SELECT osm_id, building FROM planet_osm_polygon WHERE building IS NOT NULL");
    w.commit();

    // Prepare update statement
    c.prepare("update_draw_type", 
        "UPDATE planet_osm_polygon SET draw_type = $1 WHERE osm_id = $2");

    // Vector to store updates
    std::vector<std::pair<int, int>> updates;

    // Process each row
    for (const auto& row : r)
    {
        int id = row["osm_id"].as<int>();
        std::string building = row["building"].as<std::string>();


        // Check if building type exists in mapping
        if (mapping.find(building) != mapping.end())
        {
            int drawType = mapping.find(building)->second;
            updates.push_back(std::make_pair(drawType, id));
        }
    }

    std::cout << "updates size = " << updates.size() << '\n';
    long long k = 0;
    const long long batch = 50000;
    // Perform batch update
    for (const auto& update : updates)
    {
        if ((++k) % batch == 0)
        {
            std::cout << k << '/' << updates.size() << '\n';
        }
        w.exec_prepared("update_draw_type", update.first, update.second);
    }

    w.commit();

    std::cout << "Updated " << updates.size() << " rows.\n";
}


void anamiseHelper(const std::unordered_map<std::string, int>& mapping,
                   const std::unordered_map<std::string, int>& types,
                   const std::string& col)
{
    pqxx::connection c(Conf::postgis);
    pqxx::work w(c);
    pqxx::result R = w.exec(
        "SELECT osm_id, " + col + " FROM planet_osm_polygon WHERE draw_type < 0 AND " + col + " IS NOT NULL");
    w.commit();

    std::unordered_set<std::string> set;

    for (const auto& r : R)
    {
        if (mapping.find(r[col].c_str()) == mapping.end())
            set.insert(r[col].c_str());
    }

    for (const auto& s : set)
    {
        std::cout << s << '\n';
    }
}


void analiseAreas(const std::unordered_map<std::string, int>& mapping,
                  const std::unordered_map<std::string, int>& types)
{
    anamiseHelper(mapping, types, "\"natural\"");

    
}


void realNatural(const std::unordered_map<std::string, int>& mapping)
{
    pqxx::connection c(Conf::postgis);
    pqxx::work w(c);
    pqxx::result r = w.exec(
        "SELECT osm_id, \"natural\" FROM planet_osm_polygon WHERE draw_type < 0 AND \"natural\" IS NOT NULL");
    w.commit();


    // Prepare update statement
    c.prepare("update_draw_type", 
        "UPDATE planet_osm_polygon SET draw_type = $1 WHERE osm_id = $2");

    // Vector to store updates
    std::vector<std::pair<int, int>> updates;

    // Process each row
    for (const auto& row : r)
    {
        int id = row["osm_id"].as<int>();
        std::string natural = row["natural"].as<std::string>();


        // Check if building type exists in mapping
        if (mapping.find(natural) != mapping.end())
        {
            int drawType = mapping.find(natural)->second;
            updates.push_back(std::make_pair(drawType, id));
        }
    }

    std::cout << "updates size = " << updates.size() << '\n';
    long long k = 0;
    const long long batch = 50000;
    // Perform batch update
    for (const auto& update : updates)
    {
        if ((++k) % batch == 0)
        {
            std::cout << k << '/' << updates.size() << '\n';
        }
        w.exec_prepared("update_draw_type", update.first, update.second);
    }

    w.commit();

    std::cout << "Updated " << updates.size() << " rows.\n";
}


} // namespace maykitbo::maps

