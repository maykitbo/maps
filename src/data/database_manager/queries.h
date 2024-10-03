#pragma once


#include <string>
#include <sstream>

#include "types.h"
#include "structure.h"


namespace maykitbo::maps::db
{


class Query
{
    public:
        using set_sw_t = std::vector<std::string>;
        using DBDT = DBStruct;

        static std::string sridCheck(const std::string& table);

        static std::string listTables();

        static std::string listColumns(const std::string& table);

        static std::string bboxToQueryString(const bbox_s& bbox);

        
        static std::string idListToString(const std::vector<int>& ids);

        static std::string infoById(const std::string& table, idx_t id);

        static std::string route(const std::string& table, idx_t id_1, idx_t id_2);

        static std::string fetch(   const std::string& table,
                                    const set_sw_t& select,
                                    const set_sw_t& where,
                                    unsigned long long limit);


        static std::string where(const set_sw_t& conditions);
        static std::string dareaCond(d_area_s darea);
        static std::string minDrawTypeCond(int min_draw_type);
        static std::string bboxWWayCond(const bbox_s& bbox);
        static std::string bboxWBboxCond(const bbox_s& bbox);

        static std::string select(const set_sw_t& conditions);
        static std::string columnsSelect(const set_sw_t& columns);
        static std::string wayColOutSelect();
        static std::string wayColOutSelect(float simplify_epsilon);




private:
        static std::string flat(const set_sw_t& conditions,
                                const std::string &del);









};

} // namespace maykitbo::maps::db