#pragma once


#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <list>
#include <set>
#include <nlohmann/json.hpp>

#include "config.h"
#include "postgis_connector.h"


// ALTER TABLE planet_osm_polygon
// ADD COLUMN draw_type INTEGER NOT NULL DEFAULT -1;

// ALTER TABLE planet_osm_line
// ADD COLUMN draw_type INTEGER NOT NULL DEFAULT -1;


namespace maykitbo::maps
{


// Helper function to split columns string into individual columns
std::vector<std::string> splitColumns(const std::string& columns_string)
{
    std::string str = columns_string;
    std::vector<std::string> columns;
    size_t pos = 0;
    str.erase(0, 1);
    while ((pos = str.find(", ")) != std::string::npos)
    {
        columns.push_back(str[0] == '"' ? str.substr(1, pos - 2) : str.substr(0, pos));
        str.erase(0, pos + 2);
    }
    columns.push_back(str);
    return columns;
}


void createJson(const std::string& table)
{
    auto columns = splitColumns(DBStruct::ALL_INFO_COLUMNS_POLYGON);
    for (auto col : columns) std::cout << col << ' ';
    std::cout << '\n';

    // Create a JSON object to store the result
    nlohmann::json j;

    for (const auto& col : columns)
    {
        std::cout << col << '\n';
        try
        {
            pqxx::connection c(Conf::postgis);
            pqxx::work w(c);
            pqxx::result R = w.exec(
                "SELECT DISTINCT \"" + col + "\" FROM " + table + " WHERE \"" + col + "\" IS NOT NULL;");
            
            w.commit();

            std::set<std::string> unique_values;

            // Iterate through each row in the result
            for (const auto& row : R)
            {
                // Add the value to the set
                unique_values.insert(row[col].as<std::string>());
            }

            // Add the column and its unique values to the JSON object
            j[col] = unique_values;
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    }

    // Write the JSON object to a file
    std::ofstream outFile("src/data/tune_db/" + table + "_mapping.json");
    outFile << j.dump(4); // Pretty print with indentation
}


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


void printMappingTypes(const std::unordered_map<std::string, int>& mapping,
                       const std::unordered_map<std::string, int>& types)
{
    std::cout << "_____\n\n";
    for (auto w : types)
    {
        std::cout << w.first << " | " << w.second << '\n';
    }
    std::cout << "_____\n\n";
    for (auto w : mapping)
    {
        std::cout << w.first << " | " << w.second << '\n';
    }
    std::cout << "_____\n\n";
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


void analise(const std::unordered_map<std::string, int>& mapping,
             const std::unordered_map<std::string, int>& types,
             const std::string& col,
             const std::string& table)
{
    pqxx::connection c(Conf::postgis);
    pqxx::work w(c);
    pqxx::result R = w.exec(
        "SELECT osm_id, name, draw_type, " + col + " FROM " + table + " WHERE draw_type >= 0-10 AND " + col + " IS NOT NULL");
    // "SELECT osm_id, name, draw_type, " + col + " FROM " + table + " WHERE " + col + " LIKE 'region'");
    w.commit();

    // std::unordered_set<std::string> set;
    std::unordered_map<std::string, int> map;

    // for (const auto& r : R)
    // {
    //     std::cout << r["name"].c_str() << '\n';
    // }
    // return;

    for (const auto& r : R)
    {
        if (mapping.find(r[col].c_str()) == mapping.end())
            // set.insert(r[col].c_str());
            ++map[r[col].c_str()];
    }

    for (const auto& s : map)
    {
        std::cout << s.first << "\t\t\t" << s.second << '\n';;
    }

    std::cout << "size = " << R.size() << '\n';
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

