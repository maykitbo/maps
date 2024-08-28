#include "parser.h"

#include <iostream>
#include <random>

void printBbox(unsigned idx)
{
    std::vector<float> bbox = OsmParser::getBbox(idx);
    std::cout << "bbox for idx = " << idx << ": ";
    if (bbox.size() == 0) {
        std::cout << "no such idx";
    }
    for (auto i : bbox)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

void printSomeJsonData(unsigned idx, int node_count, int way_count)
{
    nlohmann::json data = OsmParser::getJson(idx);
    for (const auto& feature : data["features"])
    {
        if (OsmParser::isNode(feature)&& 
            feature["properties"].contains("tags") &&
            --node_count >= 0)
        {
            std::cout << OsmParser::getId(feature) << '\n';
        }

        if (OsmParser::isWay(feature) && --way_count >= 0)
        {
            std::cout << OsmParser::getId(feature) << '\n';
        }
    }
}


void test3(unsigned idx, int way_count) {
    nlohmann::json data = OsmParser::getJson(idx);
    for (const auto& feature : data["features"])
    {
        if (OsmParser::isWay(feature) && --way_count >= 0)
        {
            auto a = OsmParser::getNodes(feature);
            for (auto i : a) {
                std::cout << i << ' ';
            }
            std::cout << '\n';
        }
    }
}


int main()
{
    printBbox(0);
    printBbox(4);
    printBbox(5);
    printBbox(6);

    printSomeJsonData(0, 3, 3);

    test3(0, 3);

    return 0;
}
