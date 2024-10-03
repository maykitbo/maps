#include "idata.h"


using namespace maykitbo::maps;



IData::IData(const std::string& conn_str)
    : pgc_(conn_str)
{}


const db::Connector& IData::connector()
{
    return pgc_;
}


std::string IData::infoAsString(const std::string& table, idx_t id) const
{
    pqxx::result R = pgc_.getInfoById(table, id);
    std::string info;
    for (const auto& r : R[0])
    {
        if (!r.is_null())
        {
            info += std::string(r.name()) + " = " + r.c_str() + "\n";
        }
    }
    // std::cout << info << '\n';
    // // return info;

    // R = pgc_.getInfoById(id);
    // if (!R[0][0].is_null())
    //     return R[0][0].c_str();
    // return "";
    return info;
}


std::string IData::pointInfoAsString(idx_t id) const
{
    return infoAsString(DBDT::POINT_TABLE, id);
}


std::string IData::polygonInfoAsString(idx_t id) const
{
    return infoAsString(DBDT::POLYGON_TABLE, id);
}


std::string IData::lineInfoAsString(idx_t id) const
{
    return infoAsString(DBDT::LINE_TABLE, id);
}

std::string IData::roadInfoAsString(idx_t id) const
{
    return infoAsString(DBDT::ROAD_TABLE, id);
}


void IData::route(idx_t id_1, idx_t id_2) const
{
    pqxx::result R = pgc_.createRoute(DBDT::POINT_TABLE, id_1, id_2);
    std::cout << "ROUTE START\n";

    std::cout << "\tsize = " << R.size() << '\n';

    std::cout << "ROUTE END\n";
}