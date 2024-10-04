#pragma once


#include <iostream>


#include "idata.h"
#include "config.h"
#include "time_test.h"


namespace TEMP
{

using namespace maykitbo::maps;


d_area_s maxMinArea(coord_t bbox_area)
{
    return
    {
        bbox_area / 300.0,
        bbox_area / 0.5
    };
}


void polyRequestTimeTest(float tol)
{   
    db::Connector pgc(Conf::postgis);

    maykitbo::TimeTest tt("db request");
    // auto R = pgc.fetchBbox(db::DBStruct::POLYGON_TABLE,
    //                     {56.053, 55.572, 38.4119, 36.9001},
    //                     100000,
    //                     db::Query::wayColOutTransform(tol),
    //                     {db::DBStruct::DRAW_TYPE_COL},
    //                     {db::Query::dareaCondition(maxMinArea(5.02119e+09))});
    tt.pause();
    // std::cout << "tol = " << tol << "\n\t" << tt << "\tsize = " << R.size() << "\n";
}


void test()
{
    // IData db(Conf::postgis);
    // db.fethLines()
    // db.connector().listColumns(DBStruct::POLYGON_TABLE);

    

    // for (const auto& C : R)
    // {
    //     for (const auto& F : C)
    //     {
    //         std::cout << F.name() << '\t' << F.c_str() << '\n';
    //     }
    //     std::cout << "\n";
    // }


    for (float tol : std::vector<float>{0.5})
    {
        polyRequestTimeTest(tol);
    }
}


} // namespace wkb
