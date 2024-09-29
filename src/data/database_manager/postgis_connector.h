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

        pqxx::result executeNonTransactionalQuery(const std::string& query) const;
        pqxx::result executeQuery(const std::string& query) const;
        void listTables() const;
        void listColumns(const std::string& table) const;

        pqxx::result fetchBboxDarea(const std::string& table,
                                    const bbox_s& bbox,
                                    d_area_s darea,
                                    int limit) const;
        pqxx::result fetchBboxMinDrawType(const std::string& table,
                                    const bbox_s& bbox,
                                    int min_draw_type,
                                    int limit) const;
        pqxx::result getInfoById(const std::string& table, idx_t id) const;
        
        int sridCheck(const std::string& table) const;

    protected:
        pqxx::connection* connect() const;

        std::string conn_str_;

        void handleException(const std::exception& e) const;
};


} // namespace maykitbo::maps
