#include "connector.h"


using namespace maykitbo::maps::db;


Connector::Connector(const std::string& conn_str)
    : conn_str_(conn_str) {}


Connector::~Connector()
{
    LOG << MESSAGE << "close" << LOG;
}


void Connector::handleException(const std::exception& e) const
{
    LOG << ERROR << "cathed error: " << e.what() << LOG;
}


pqxx::connection* Connector::connect() const
{
    try
    {
        // Initialize the connection if it hasn't been created yet
        // static thread_local pqxx::connection C(conn_str_);
        // C = pqxx::connection(conn_str_);
        // return &C;
        static thread_local std::unique_ptr<pqxx::connection> C;
        if (!C)
        {
            C = std::make_unique<pqxx::connection>(conn_str_);
            LOG << MESSAGE << "Opened database connection in thread: " << std::this_thread::get_id() << LOG;
        }
        return C.get();

    }
    catch (const std::exception &e)
    {
        LOG << ERROR << "Failed to connect to database: " << e.what() << ", in thread: " << std::this_thread::get_id() << LOG;
    }
    return nullptr;
}



pqxx::result Connector::executeNonTransactionalQuery(const std::string& query) const
{
    try
    {
        pqxx::nontransaction N(*connect());
        pqxx::result R = N.exec(query);
        LOG << MESSAGE << "Query executed successfully, in thread: " << std::this_thread::get_id() << LOG;
        if (R.empty())
        {
            LOG << WARNING << "No data fund in thread " << std::this_thread::get_id() << LOG;
            return pqxx::result{};
        }
            return R;
        }
    catch (const std::exception &e)
    {
        handleException(e);
        return pqxx::result();
    }
}


pqxx::result Connector::executeQuery(const std::string& query) const
{
    try
    {
        pqxx::work W(*connect());
        pqxx::result r = W.exec(query);
        W.commit();
        LOG << MESSAGE << "Query executed successfully" << LOG;
        return r;
    }
    catch (const std::exception& e)
    {
        LOG << ERROR << "Error: " << e.what() << LOG;
        return pqxx::result();;
    }
    return pqxx::result();
}


int Connector::sridCheck(const std::string& table) const
{
    auto result = executeNonTransactionalQuery(
        Query::sridCheck(table));

    if (result.empty())
    {
        LOG << ERROR << "Failed to retrieve SRID from the table." << LOG;
        return -1;
    }
    else if (result[0][0].as<int>() != DBStruct::SRID_IN)
    {
        LOG << WARNING << "Srid in the table does not math expected srid." << LOG;
    }
    return result[0][0].as<int>();
}


void Connector::listTables() const
{
    pqxx::result R = executeNonTransactionalQuery(
        Query::listTables());

    std::cout << "Table Name\tSize (bytes)\n";
    for (auto row : R)
        std::cout << row[0].c_str() << "\t" << row[1].as<long long>() << '\n';   
}


void Connector::listColumns(const std::string& table) const
{
    pqxx::result R = executeNonTransactionalQuery(
        Query::listColumns(table));

    std::cout << "Columns in " + table + ":\n";
    for (pqxx::result::size_type i = 0; i < R.size(); ++i)
        std::cout << '\t' << i << ": " << R[i][0].c_str() << '\n';
}


pqxx::result Connector::getInfoById(const std::string& table, idx_t id) const
{
    pqxx::result R = executeNonTransactionalQuery(
        Query::infoById(table, id)
    );

    LOG << MESSAGE << "id " << std::to_string(id) << ". data found successfully" << LOG;

    return R;
}


// pqxx::result Connector::getInfoById(idx_t id) const
// {
//     pqxx::result R = executeNonTransactionalQuery(
//         Query::infoById(id)
//     );
//     LOG << MESSAGE << "id " << std::to_string(id) << ". data found successfully" << LOG;
//     return R;
// }



pqxx::result Connector::fetch(  const std::string& table,
                                const std::vector<std::string>& s,
                                const std::vector<std::string>& w,
                                unsigned long long limit) const
{
    pqxx::result R = executeNonTransactionalQuery(
        Query::fetch(table, s, w, limit));

    LOG << MESSAGE <<
        "Data fetched successfully in " << table <<
    LOG;

    return R;
}


// pqxx::result Connector::fetchBbox(const std::string& table,
//                         const bbox_s& bbox,
//                         int limit,
//                         const std::string &out_tranform,
//                         const std::vector<std::string>& columns,
//                         const std::vector<std::string>& conditions) const
// {
//     pqxx::result R = executeNonTransactionalQuery(
//         Query::bbox(table, bbox, limit, out_tranform, columns, conditions));

//     LOG << MESSAGE <<
//         "draw data fetched successfully in " << table <<
//         ", bbox = " << Query::bboxToQueryString(bbox) <<
//     LOG;

//     return R;
// }


// pqxx::result Connector::fetchBboxDarea(const std::string& table,
//                                         const bbox_s& bbox,
//                                         d_area_s darea,
//                                         int limit,
//                                         const std::string& columns) const
// {
//     pqxx::result R = executeNonTransactionalQuery(
//         Query::bboxDarea(table, bbox, darea, limit, columns));

//     LOG << MESSAGE <<
//         "draw data fetched successfully in " << table <<
//         ", bbox = " << Query::bboxToQueryString(bbox) <<
//         ", area.min = " << darea.min <<
//         ", dare.max = " << darea.max <<
//     LOG;

//     return R;
// }


// pqxx::result Connector::fetchBboxMinDrawType(const std::string& table,
//                             const bbox_s& bbox,
//                             int min_draw_type,
//                             int limit) const
// {
//     pqxx::result R = executeNonTransactionalQuery(
//         Query::bboxMinDrawType(table, bbox, min_draw_type, limit)
//     );

//     LOG << MESSAGE <<
//         "darw data fetched successfully in " << table <<
//         ", bbox = " << Query::bboxToQueryString(bbox) <<
//         ", min draw type = " << min_draw_type <<
//     LOG;

//     return R;
// }


pqxx::result Connector::createRoute(const std::string& table, idx_t id_1, idx_t id_2) const
{
    pqxx::result R = executeNonTransactionalQuery(
        Query::route(table, id_1, id_2)
    );

    LOG << MESSAGE <<
        "success" << LOG;

    return R;
}


// 
