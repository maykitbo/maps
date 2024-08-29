#include "algebra.h"

#include <unordered_set>

#include <iostream>

using namespace maykitbo::maps;


int main() {
    // int exists = 0;
    // int nodes = 0;
    // auto data = OsmParser::getJson(4);
    // for (const auto& feature : OsmParser::getFeatures(data))
    // {
    //     if (OsmParser::isNode(feature))
    //     {
    //         ++nodes;
    //     }
    // }

    // std::unordered_set<long long> s;
    // for (const auto& feature : OsmParser::getFeatures(data))
    // {
    //     if (OsmParser::isWay(feature))
    //     {
    //         for (long long i : OsmParser::getNodes(feature))
    //         {
    //             s.insert(i);
    //         }
    //     }
    // }
    // std::cout << s.size() << ' ' << nodes << '\n';

    std::cout << Algebra::distanse(10.3723421, 107.0744828, 10.4197409, 107.1502662) << '\n';

    return 0;
}
