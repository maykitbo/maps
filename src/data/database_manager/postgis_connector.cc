#include "postgis_connector.h"


using namespace maykitbo::maps;


void PostGISConnector::handleException(const std::exception& e) const
{
    std::cerr << "PostGisConnector Error: " << e.what() << '\n';
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


int PostGISConnector::sridCheck(const std::string& table) const
{
    auto result = executeNonTransactionalQuery(
        PostGisQuery::sridCheck(table));
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


pqxx::result PostGISConnector::executeNonTransactionalQuery(const std::string& query) const
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
        return pqxx::result();
    }
}


void PostGISConnector::listTables() const
{
    pqxx::result R = executeNonTransactionalQuery(
        PostGisQuery::listTables());

    std::cout << "Table Name\tSize (bytes)\n";
    for (auto row : R)
        std::cout << row[0].c_str() << "\t" << row[1].as<long long>() << '\n';   
}


void PostGISConnector::listColumns(const std::string& table) const
{
    pqxx::result R = executeNonTransactionalQuery(
        PostGisQuery::listColumns(table));

    std::cout << "Columns in " + table + ":\n";
    for (pqxx::result::size_type i = 0; i < R.size(); ++i)
        std::cout << '\t' << i << ": " << R[i][0].c_str() << '\n';
}

nlohmann::json PostGISConnector::fetchGeoJsonByBBOX(const std::string& table,
                                                const bbox_s& bbox,
                                                int srid_out) const
{
    srid_ = sridCheck(table);
    // std::cout << "SRID in " << table << " = " << srid_ << '\n';

    // std::cout << PostGisQuery::BBOXtoGeoJson(table, bbox, srid_out, srid_) << "\n\n";
    pqxx::result R = executeNonTransactionalQuery(
        PostGisQuery::BBOXtoGeoJson(table, bbox, srid_out, srid_));

    // std::cout << R.size() << " " << R[0].size() << '\n';
    // std::cout << R[0][0].size() << '\n';

    if (R.empty())
    {
        std::cout << "No data fund\n";
        return nlohmann::json::object();
    }

    std::cout << "GeoJSON data fetched successfully for " << table << "\n";
    return nlohmann::json::parse(std::move(R[0][0].c_str()));
}

