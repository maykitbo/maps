#include "postgis_connector.h"


using namespace maykitbo::maps;


void PostGISConnector::handleException(const std::exception& e)
{
    std::cerr << "Error: " << e.what() << '\n';
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


void PostGISConnector::listTablesAndSizes()
{
    std::string query = "SELECT table_name, pg_total_relation_size(quote_ident(table_name))"
                        "AS size FROM information_schema.tables WHERE table_schema='public';";
    pqxx::result R = executeNonTransactionalQuery(query);
    std::cout << "Table Name\tSize (bytes)\n";
    for (auto row : R)
    {
        std::cout << row[0].c_str() << "\t" << row[1].as<int>() << '\n';
    }
}


void PostGISConnector::fetchGeoJSONByBBOX(const std::string& table,
                                        fp_type xmin, fp_type ymin,
                                        fp_type xmax, fp_type ymax)
{
    std::string query = "SELECT jsonb_build_object("
                        "'type', 'FeatureCollection',"
                        "'features', jsonb_agg(feature)"
                        ") AS geojson "
                        "FROM ("
                        "SELECT jsonb_build_object("
                        "'type', 'Feature',"
                        "'geometry', ST_AsGeoJSON(geom)::jsonb,"
                        "'properties', to_jsonb(row) - 'geom'"
                        ") AS feature "
                        "FROM ("
                        "SELECT *, geom "
                        "FROM " + table + " "
                        "WHERE geom && ST_MakeEnvelope(" +
                        std::to_string(xmin) + ", " +
                        std::to_string(ymin) + ", " +
                        std::to_string(xmax) + ", " +
                        std::to_string(ymax) + ", 4326)"
                        ") AS row"
                        ") AS features;";

    pqxx::result R = executeNonTransactionalQuery(query);
    if (!R.empty())
        std::cout << R[0][0].c_str() << '\n';
    else
        std::cout << "No data found.\n";
}

