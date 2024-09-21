#include "tune.h"


using namespace maykitbo::maps;


int main()
{
    auto tt = readPolygonMapping("src/data/tune_db/natural.ntoc");
    std::unordered_map<std::string, int> mapping =
        std::move(tt.second);
    std::unordered_map<std::string, int> types =
        std::move(tt.first);

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

    // return 0;

    realNatural(mapping);

    

    return 0;
}