#pragma once


#include <iostream>
#include <thread>
#include <memory>

#include <pqxx/pqxx>

#include "types.h"
#include "queries.h"
#include "log.h"
#include "structure.h"


namespace maykitbo::maps::db
{


class Connector
{
    mutable Log<true> LOG{std::string{"PstgisConnector.log"}};

    public:
        using fp_type = coord_t;

        Connector(const std::string& conn_str);
        ~Connector();

        pqxx::result executeNonTransactionalQuery(const std::string& query) const;
        pqxx::result executeQuery(const std::string& query) const;
        void listTables() const;
        void listColumns(const std::string& table) const;

        // pqxx::result fetchBboxDarea(const std::string& table,
        //                             const bbox_s& bbox,
        //                             d_area_s darea,
        //                             int limit,
        //                             const std::string& columns) const;
        // pqxx::result fetchBboxMinDrawType(const std::string& table,
        //                             const bbox_s& bbox,
        //                             int min_draw_type,
        //                             int limit) const;
        // pqxx::result fetchBbox(const std::string& table,
        //                         const bbox_s& bbox,
        //                         int limit,
        //                         const std::string &out_tranform,
        //                         const std::vector<std::string>& columns,
        //                         const std::vector<std::string>& conditions) const;
        pqxx::result fetch( const std::string& table,
                            const std::vector<std::string>& select,
                            const std::vector<std::string>& where,
                            unsigned long long limit) const;
        pqxx::result getInfoById(const std::string& table, idx_t id) const;
        // pqxx::result getInfoById(idx_t id) const;

        pqxx::result createRoute(const std::string& table, idx_t id_1, idx_t id_2) const;
        
        int sridCheck(const std::string& table) const;

    protected:
        pqxx::connection* connect() const;

        std::string conn_str_;

        void handleException(const std::exception& e) const;
};


} // namespace maykitbo::maps::db
