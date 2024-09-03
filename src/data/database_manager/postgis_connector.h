#pragma once


#include <iostream>
#include <pqxx/pqxx>


namespace maykitbo::maps
{


class PostGISConnector
{
    public:
        using fp_type = double;

        PostGISConnector() = default;
        ~PostGISConnector();

        void connect(const std::string& conn_str);
        void executeQuery(const std::string& query);
        pqxx::result executeNonTransactionalQuery(const std::string& query);
        void fetchData(const std::string& query);
        void listTablesAndSizes();
        void fetchGeoJSONByBBOX(const std::string& table, fp_type xmin, fp_type ymin, fp_type xmax, fp_type ymax);
    
    protected:
        std::string conn_str_;
        pqxx::connection *c_ = nullptr;

        void handleException(const std::exception& e);
        void disconnect();
};


} // namespace maykitbo::maps
