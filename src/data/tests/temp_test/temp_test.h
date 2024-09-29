#pragma once


#include <iostream>


#include "idata.h"
#include "config.h"


namespace TEMP
{

using namespace maykitbo::maps;

void test()
{
    IData db(Conf::postgis);
    // db.fethLines()
    db.connector().listColumns(DBStruct::POLYGON_TABLE);
}


} // namespace wkb
