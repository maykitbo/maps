#include "queries.h"


using namespace maykitbo::maps;
using namespace db;


std::string Query::sridCheck(const std::string& table) {
    return "SELECT ST_SRID(way) FROM " +
        std::move(table) +
        " LIMIT 1;";
}

std::string Query::listTables()
{
    return "SELECT table_name, pg_total_relation_size(quote_ident(table_name))"
    "AS size FROM information_schema.tables WHERE table_schema='public';";
}

std::string Query::listColumns(const std::string& table)
{
    return "SELECT column_name FROM information_schema.columns WHERE "
                        "table_name = '" + table + "';";
}

std::string Query::bboxToQueryString(const bbox_s& bbox)
{
    return std::to_string(bbox.min_lon) + ", " +
        std::to_string(bbox.min_lat) + ", " +
        std::to_string(bbox.max_lon) + ", " +
        std::to_string(bbox.max_lat);
}


std::string Query::idListToString(const std::vector<int>& ids) {
    std::ostringstream oss;
    for (size_t i = 0; i < ids.size(); ++i) {
        if (i != 0) oss << ",";
        oss << ids[i];
    }
    return oss.str();
}

std::string Query::infoById(const std::string& table, idx_t id)
{
    return
        "SELECT " + DBDT::ALL_INFO_COLUMNS +
        " FROM " + table +
        " WHERE " + DBDT::ID_COL + " = " + std::to_string(id) + ";";
}

std::string Query::route(const std::string& table, idx_t id_1, idx_t id_2)
{
    // return "select pgr_dijkstra("
    //             "`SELECT * FROM " + table + "', " +
    //             std::to_string(id_1) + ", " + std::to_string(id_2) +
    //         ");";

    return
        "SELECT * FROM pgr_Dijkstra("
            "'select id, source, target, cost, reverse_cost from edges', " +
            std::to_string(id_1) + ", " + std::to_string(id_2) + ", true" +
        ");";
}







//// ********* WHERE *************************************************************************

std::string Query::dareaCond(d_area_s darea)
{
    return
        DBDT::WAY_AREA_COL + " > " + std::to_string(darea.min) +
        " AND " + DBDT::WAY_AREA_COL + " < " + std::to_string(darea.max);
}

std::string Query::minDrawTypeCond(int min_draw_type)
{
    return DBDT::DRAW_TYPE_COL + " >= " + std::to_string(min_draw_type);
}

std::string Query::bboxWWayCond(const bbox_s& bbox)
{
    return
        // DBDT::WAY_COL +
        // " && " +
        // "ST_Transform("
        //     "ST_MakeEnvelope(" +
        //         bboxToQueryString(bbox) + ", " +
        //         std::to_string(DBDT::SRID_OUT) +
        //     "), " +
        //     std::to_string(DBDT::SRID_IN) +
        // ")";
        DBDT::WAY_COL +
        " && " +
        "ST_MakeEnvelope(" +
            bboxToQueryString(bbox) + ", " +
            std::to_string(DBDT::SRID_IN) +
        ")";
}

std::string Query::bboxWWayAsBboxCond(const bbox_s& bbox)
{
    return
        "ST_Transform(ST_Envelope(" + DBDT::WAY_COL + "), 4326) "
        // "ST_Envelope(" + DBDT::WAY_COL + ") "
        " && " +
        // "ST_Transform(" +
            "ST_MakeEnvelope(" +
                bboxToQueryString(bbox) + ", " +
                std::to_string(DBDT::SRID_OUT) +
            // "), " +
            // std::to_string(DBDT::SRID_IN) +
        ")";
}

std::string Query::bboxWBboxCond(const bbox_s& bbox)
{
    return
        "ST_Transform(" + DBDT::BBOX_COL + ", 4326)"
        " @ "
        "ST_MakeEnvelope(" +
            bboxToQueryString(bbox) + ", " +
            std::to_string(DBDT::SRID_OUT) +
        ")";
}

std::string Query::sizeOfWayInBytesCond(int threshold)
{
    return "ST_MemSize(" + DBDT::WAY_COL + ") > " + std::to_string(threshold);
}

//// ********* SELECT *************************************************************************


std::string Query::wayColOutSelect()
{
    return
        "ST_AsText("
            "ST_Transform(" +
                DBDT::WAY_COL + ", " + 
                std::to_string(DBDT::SRID_OUT) +
            ")"
        ") AS " + DBDT::TEXT_WAY_COL;
}

std::string Query::wayAsInSridSelect()
{
    return
        "ST_AsText(" +
            DBDT::WAY_COL +
        ") AS " + DBDT::PROJECTED_WAY;

}

std::string Query::wayColOutSelect(float simplify_epsilon)
{
    return
        "ST_AsText("
            "ST_Transform("
                "ST_SimplifyPolygonHull(" +
                    DBDT::WAY_COL + ", " + std::to_string(simplify_epsilon) +
                "), " +
                std::to_string(DBDT::SRID_OUT) +
            ")"
        ") AS " + DBDT::TEXT_WAY_COL;
}

std::string Query::columnsSelect(const std::vector<std::string>& columns)
{
    return flat(columns, ", ");
}

//// ********* COMMON *************************************************************************


std::string Query::flat(const std::vector<std::string>& conditions,
                        const std::string &del)
{
    std::string res = "";
    for (size_t k = 0; k < conditions.size() - 1; ++k)
    {
        res += conditions[k] + del;
    }
    if (conditions.size())
        res += conditions.back();
    return res;
}

std::string Query::where(const std::vector<std::string>& conditions)
{
    return flat(conditions, " AND ");
}


std::string Query::select(const std::vector<std::string>& conditions)
{
    return flat(conditions, ", ");
}


std::string Query::fetch(const std::string& table,
                         const std::vector<std::string>& s,
                         const std::vector<std::string>& w,
                         unsigned long long limit)
{
    return
        "SELECT " + select(s) +
        " FROM " + table +
        " WHERE " + where(w) +
        " LIMIT " + std::to_string(limit) + ";";
}
