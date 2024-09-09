#pragma once


#include <iostream>
#include <pqxx/pqxx>
#include <nlohmann/json.hpp>

#include "types.h"
#include "queries.h"


namespace maykitbo::maps
{


class PostGISConnector
{
    public:
        using fp_type = coord_t;

        PostGISConnector() = default;
        ~PostGISConnector();

        void connect(const std::string& conn_str);
        void executeQuery(const std::string& query);
        pqxx::result executeNonTransactionalQuery(const std::string& query) const;
        void listTables() const;
        nlohmann::json fetchGeoJsonByBBOX(const std::string& table,
                                    const bbox_s& bbox,
                                    int srid_out = 4326) const;
        void listColumns(const std::string& table) const;

        int getSRID() const { return srid_; }

    protected:
        std::string conn_str_;
        pqxx::connection *c_ = nullptr;

        mutable int srid_;

        void handleException(const std::exception& e) const;
        void disconnect();

        int sridCheck(const std::string& table) const;
        nlohmann::json toNlohman() const;
};


} // namespace maykitbo::maps
