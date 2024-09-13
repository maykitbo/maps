#pragma once


#include <iostream>
#include <thread>
#include <pqxx/pqxx>
#include <nlohmann/json.hpp>

#include "types.h"
#include "queries.h"
#include "log.h"


namespace maykitbo::maps
{


class PostGISConnector
{
    mutable Log<true> LOG{std::string{"PstgisConnector.log"}};

    public:
        using fp_type = coord_t;

        PostGISConnector(const std::string& conn_str);
        ~PostGISConnector();

        // void connect(const std::string& conn_str);
        pqxx::result executeNonTransactionalQuery(const std::string& query) const;
        pqxx::result executeQuery(const std::string& query) const;
        void listTables() const;
        nlohmann::json fetchGeoJsonByBBOX(const std::string& table,
                                    const bbox_s& bbox,
                                    d_area_s darea,
                                    int srid_out = 4326) const;
        nlohmann::json fetchGeoJsonByBBOX(const std::string& table,
                            const bbox_s& bbox,
                            int srid_out = 4326) const;
        void listColumns(const std::string& table) const;

        int getSRID() const { return srid_; }

    protected:
        std::string conn_str_;
        pqxx::connection *c_ = nullptr;

        mutable int srid_ = 3857;

        void handleException(const std::exception& e) const;
        void disconnect();


        int sridCheck(const std::string& table) const;
        nlohmann::json toNlohman() const;
};


} // namespace maykitbo::maps
