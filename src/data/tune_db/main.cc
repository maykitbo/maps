#include "tune.h"


using namespace maykitbo::maps;


int main()
{
    auto polygin_mapping = readPolygonMapping("src/data/tune_db/lines.ntoc");
    std::unordered_map<std::string, int> mapping =
        std::move(polygin_mapping.second);
    std::unordered_map<std::string, int> types =
        std::move(polygin_mapping.first);

    // std::cout << "_____\n\n";
    // for (auto w : types)
    // {
    //     std::cout << w.first << " | " << w.second << '\n';
    // }
    // std::cout << "_____\n\n";
    // for (auto w : mapping)
    // {
    //     std::cout << w.first << " | " << w.second << '\n';
    // }
    // std::cout << "_____\n\n";

    realLines(mapping);

    

    return 0;
}