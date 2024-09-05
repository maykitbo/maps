#pragma once


#include <iostream>
#include <pqxx/pqxx>

#include "types.h"


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
        pqxx::result executeNonTransactionalQuery(const std::string& query);
        void fetchData(const std::string& query);
        void listTables();
        pqxx::result fetchGeoJSONByBBOX(const std::string& table,
                                        const bbox_s& bbox,
                                        int srid_out = 4326);
        void listColumns(const std::string& table);

        int getSRID() const { return srid_; }

    protected:
        std::string conn_str_;
        pqxx::connection *c_ = nullptr;

        int srid_;

        void handleException(const std::exception& e);
        void disconnect();

        int sridCheck(const std::string& table);

        std::string bboxToQueryString(const bbox_s& bbox);
};


} // namespace maykitbo::maps
