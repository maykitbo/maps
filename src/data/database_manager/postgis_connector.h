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
        void listTables();
        pqxx::result fetchGeoJSONByBBOX(const std::string& table,
                                        fp_type xmin, fp_type ymin,
                                        fp_type xmax, fp_type ymax,
                                        int srid_out = 4326);
        void listColumns(const std::string& table);

        int getSRID() const { return srid_; }


        // debug
        pqxx::result fetchGeometriesByBBOX(const std::string& table,
                                fp_type xmin, fp_type ymin,
                                fp_type xmax, fp_type ymax);
        void fetchInitialData(const std::string& table, int limit = 10);

    protected:
        std::string conn_str_;
        pqxx::connection *c_ = nullptr;

        int srid_;

        void handleException(const std::exception& e);
        void disconnect();

        int sridCheck(const std::string& table);
};


} // namespace maykitbo::maps
