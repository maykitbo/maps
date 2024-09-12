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





    IData db;


    auto R = db.fetchPolygons(bbox_s{55.816, 55.81, 37.667, 37.655});



    return 0;
}   


