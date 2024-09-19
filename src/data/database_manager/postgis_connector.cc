#include "postgis_connector.h"


using namespace maykitbo::maps;


PostGISConnector::PostGISConnector(const std::string& conn_str)
    : conn_str_(conn_str) {}


PostGISConnector::~PostGISConnector()
{
    LOG << MESSAGE << "close" << LOG;
}


void PostGISConnector::handleException(const std::exception& e) const
{
    LOG << ERROR << "cathed error: " << e.what() << LOG;
}


pqxx::connection* PostGISConnector::connect()
{
    try
    {
        static thread_local std::unique_ptr<pqxx::connection> C;

        // Initialize the connection if it hasn't been created yet
        if (!C) {
            C = std::make_unique<pqxx::connection>(conn_str_);
            LOG << MESSAGE << "Opened database connection in thread: " << std::this_thread::get_id() << LOG;
        }
        return C.get();
    }
    catch (const std::exception &e)
    {
        LOG << ERROR << "cathed error: " << e.what() << LOG;
    }
    return nullptr;
}


pqxx::result PostGISConnector::executeNonTransactionalQuery(const std::string& query)
{
    try
    {
        pqxx::nontransaction N(*connect());
        pqxx::result R = N.exec(query);
        LOG << MESSAGE << "Query executed successfully" << LOG;
        return R;
    }
    catch (const std::exception &e)
    {
        handleException(e);
        return pqxx::result();
    }
}


pqxx::result PostGISConnector::executeQuery(const std::string& query)
{
    try
    {
        pqxx::work W(*connect());
        pqxx::result r = W.exec(query);
        W.commit();
        LOG << MESSAGE << "Query executed successfully" << LOG;
        return r;
    }
    catch (const std::exception& e)
    {
        LOG << ERROR << "Error: " << e.what() << LOG;
        return pqxx::result();;
    }
    return pqxx::result();
}


int PostGISConnector::sridCheck(const std::string& table)
{
    auto result = executeNonTransactionalQuery(
        PostGisQuery::sridCheck(table));

    if (result.empty())
    {
        LOG << ERROR << "Failed to retrieve SRID from the table." << LOG;
        return -1;
    }
    else if (result[0][0].as<int>() != DBStruct::SRID)
    {
        LOG << WARNING << "Srid in the table does not math expected srid." << LOG;
    }
    return result[0][0].as<int>();
}


void PostGISConnector::listTables()
{
    pqxx::result R = executeNonTransactionalQuery(
        PostGisQuery::listTables());

    std::cout << "Table Name\tSize (bytes)\n";
    for (auto row : R)
        std::cout << row[0].c_str() << "\t" << row[1].as<long long>() << '\n';   
}


void PostGISConnector::listColumns(const std::string& table)
{
    pqxx::result R = executeNonTransactionalQuery(
        PostGisQuery::listColumns(table));

    std::cout << "Columns in " + table + ":\n";
    for (pqxx::result::size_type i = 0; i < R.size(); ++i)
        std::cout << '\t' << i << ": " << R[i][0].c_str() << '\n';
}

// nlohmann::json PostGISConnector::fetchGeoJsonByBBOX(const std::string& table,
//                                                 const bbox_s& bbox,
//                                                 d_area_s darea,
//                                                 int srid_out) const
// {
//     pqxx::result R = executeNonTransactionalQuery(
//         PostGisQuery::BBOXtoGeoJson(table, bbox, darea, srid_out));

//     if (R.empty())
//     {
//         LOG << WARNING << "No data fund" << LOG;
//         return nlohmann::json::object();
//     }

//     LOG <<
//         MESSAGE <<
//         "GeoJSON data fetched successfully for " <<
//         table <<
//         " with bbox = " <<
//         PostGisQuery::bboxToQueryString(bbox) <<
//     LOG;

//     return nlohmann::json::parse(std::move(R[0][0].c_str()));
// }


// nlohmann::json PostGISConnector::fetchGeoJsonByBBOX(const std::string& table,
//                                                 const bbox_s& bbox,
//                                                 int srid_out) const
// {
//     pqxx::result R = executeNonTransactionalQuery(
//         PostGisQuery::BBOXtoGeoJson(table, bbox, srid_out, srid_));

//     if (R.empty())
//     {
//         LOG << WARNING << "No data fund" << LOG;
//         return nlohmann::json::object();
//     }

//     LOG <<
//         MESSAGE <<
//         "GeoJSON data fetched successfully for " <<
//         table <<
//         " with bbox = " <<
//         PostGisQuery::bboxToQueryString(bbox) <<
//     LOG;

//     return nlohmann::json::parse(std::move(R[0][0].c_str()));
// }


pqxx::result PostGISConnector::fetchDraw(const std::string& table,
                                        const bbox_s& bbox,
                                        d_area_s darea,
                                        int srid_out)
{
    pqxx::result R = executeNonTransactionalQuery(
        PostGisQuery::bboxAreaDraw(table, bbox, darea, srid_out));
    // std::cout << PostGisQuery::bboxAreaDraw(table, bbox, darea, srid_out, srid_) << '\n';
    if (R.empty())
    {
        LOG << WARNING << "No data fund" << LOG;
        return pqxx::result{};
    }

    LOG << MESSAGE <<
        "GeoJSON data for drawing fetched successfully for " << table <<
        " with bbox = " << PostGisQuery::bboxToQueryString(bbox) <<
        " with area.min = " << darea.min <<
        " | dare.max = " << darea.max <<
    LOG;

    return R;
}


