#include "postgis_connector.h"


using namespace maykitbo::maps;


void PostGISConnector::handleException(const std::exception& e)
{
    std::cerr << "M Error: " << e.what() << '\n';
}


void PostGISConnector::disconnect()
{
    if (c_ != nullptr)
    {
        c_->close();
        delete c_;
        c_ = nullptr;
    }
}


PostGISConnector::~PostGISConnector()
{
    disconnect();
}


void PostGISConnector::connect(const std::string& conn_str)
{
    conn_str_ = conn_str;
    disconnect();
    try
    {
        c_ = new pqxx::connection(conn_str_);
        if (c_->is_open())
            std::cout << "Opened database successfully: " << c_->dbname() << '\n';
        else
            std::cout << "Can't open database\n";
    }
    catch (const std::exception &e)
    {
        handleException(e);
    }
}


int PostGISConnector::sridCheck(const std::string& table)
{
    std::string query = "SELECT ST_SRID(way) FROM " + table + " LIMIT 1;";
    auto result = executeNonTransactionalQuery(query);
    if (result.empty()) {
        std::cerr << "Failed to retrieve SRID from the table.\n";
        return -1;
    }
    return result[0][0].as<int>();
}


void PostGISConnector::executeQuery(const std::string& query)
{
    try
    {
        pqxx::work W(*c_);
        W.exec(query);
        W.commit();
        std::cout << "Query executed successfully\n";
    }
    catch (const std::exception &e)
    {
        handleException(e);
    }
}


pqxx::result PostGISConnector::executeNonTransactionalQuery(const std::string& query)
{
    try
    {
        pqxx::nontransaction N(*c_);
        pqxx::result R = N.exec(query);
        std::cout << "Query executed successfully\n";
        return R;
    }
    catch (const std::exception &e)
    {
        handleException(e);
        return pqxx::result(); // Return an empty result on failure
    }
}


void PostGISConnector::fetchData(const std::string& query)
{
    pqxx::result R = executeNonTransactionalQuery(query);
    for (auto row : R)
    {
        for (auto field : row)
        {
            std::cout << field.c_str() << '\t';
        }
        std::cout << '\n';
    }
}


void PostGISConnector::listTables()
{
    std::string query = "SELECT table_name, pg_total_relation_size(quote_ident(table_name))"
                        "AS size FROM information_schema.tables WHERE table_schema='public';";
    pqxx::result R = executeNonTransactionalQuery(query);
    std::cout << "Table Name\tSize (bytes)\n";
    for (auto row : R)
    {
        std::cout << row[0].c_str() << "\t" << row[1].as<long long>() << '\n';   
    }
}


void PostGISConnector::listColumns(const std::string& table)
{
    std::string columnCheckQuery = "SELECT column_name FROM information_schema.columns WHERE "
                                "table_name = '" + table + "';";
    auto columnCheckResult = executeNonTransactionalQuery(columnCheckQuery);
    std::cout << "Columns in " + table + ":\n";
    for (auto row : columnCheckResult) {
        std::cout << '\t' << row[0].c_str() << '\n';
    }
}


pqxx::result PostGISConnector::fetchGeoJSONByBBOX(const std::string& table,
                                                const bbox_s& bbox,
                                                int srid_out)
{
    srid_ = sridCheck(table);
    std::cout << "SRID in " << table << " = " << srid_ << '\n';

    std::string query = R"(
        SELECT *
        FROM planet_osm_roads
        WHERE planet_osm_roads.way && ST_Transform(
            ST_MakeEnvelope()" +
                bboxToQueryString(bbox) + ", " +
                std::to_string(srid_out) + "), " +
            std::to_string(srid_) +
        ");";

    pqxx::result R = executeNonTransactionalQuery(query);
    std::cout << "GeoJSON data fetched successfully\n";

    if (R.empty())
        std::cout << "No data fund\n";

    return R;
}


std::string PostGISConnector::bboxToQueryString(const bbox_s& bbox)
{
    return std::to_string(bbox.left_top.lon) + ", " +
           std::to_string(bbox.right_buttom.lat) + ", " +
           std::to_string(bbox.right_buttom.lon) + ", " +
           std::to_string(bbox.left_top.lat);
}

