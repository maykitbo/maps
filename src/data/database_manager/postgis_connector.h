#pragma once


#include <iostream>
#include <thread>
#include <memory>

#include <pqxx/pqxx>
// #include <nlohmann/json.hpp>

#include "types.h"
#include "queries.h"
#include "log.h"
// #include "config.h"
#include "database_structure.h"


namespace maykitbo::maps
{


class PostGISConnector
{
    mutable Log<true> LOG{std::string{"PstgisConnector.log"}};

    public:
        using fp_type = coord_t;

        PostGISConnector(const std::string& conn_str);
        ~PostGISConnector();

        pqxx::result executeNonTransactionalQuery(const std::string& query);
        pqxx::result executeQuery(const std::string& query);
        void listTables();
        // nlohmann::json fetchGeoJsonByBBOX(const std::string& table,
        //                             const bbox_s& bbox,
        //                             d_area_s darea,
        //                             int srid_out = 4326) const;
        // nlohmann::json fetchGeoJsonByBBOX(const std::string& table,
        //                     const bbox_s& bbox,
        //                     int srid_out = 4326) const;
        void listColumns(const std::string& table);

        pqxx::result fetchDraw(const std::string& table,
                                    const bbox_s& bbox,
                                    d_area_s darea,
                                    int srid_out = 4326);

    protected:
        // static thread_local std::unique_ptr<pqxx::connection> C;

        pqxx::connection* connect();

        std::string conn_str_;
        // pqxx::connection *c_ = nullptr;

        // mutable int srid_ = 3857;

        void handleException(const std::exception& e) const;
        // void disconnect();


        int sridCheck(const std::string& table);
};


} // namespace maykitbo::maps
