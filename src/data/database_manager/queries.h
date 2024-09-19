#pragma once


#include <string>

#include "types.h"
#include "database_structure.h"


namespace maykitbo::maps
{


class PostGisQuery
{
    public:
        using DBDT = DBStruct;

        static std::string sridCheck(const std::string& table) {
            return "SELECT ST_SRID(way) FROM " +
                std::move(table) +
                " LIMIT 1;";
        }

        static std::string listTables()
        {
            return "SELECT table_name, pg_total_relation_size(quote_ident(table_name))"
            "AS size FROM information_schema.tables WHERE table_schema='public';";
        }

        static std::string listColumns(const std::string& table)
        {
            return "SELECT column_name FROM information_schema.columns WHERE "
                                "table_name = '" + table + "';";
        }

        // static std::string BBOXtoGeoJson(const std::string& table,
        //                                 const bbox_s& bbox,
        //                                 d_area_s darea,
        //                                 int srid_out,
        //                                 int srid_in)
        // {
        // std::string srid_out_s = std::to_string(srid_out);
        // std::string srid_in_s = std::to_string(srid_in);

        // return R"(
        //     SELECT jsonb_build_object(
        //     'type',     'FeatureCollection',
        //     'features', jsonb_agg(features.feature)
        //     )
        //     FROM (
        //         SELECT jsonb_build_object(
        //             'type',         'Feature',
        //             'geometry',     ST_AsGeoJSON(ST_Transform(
        //                                     way, )" +
        //                                     srid_out_s +
        //                                 R"()
        //                             )::jsonb,
        //             'properties',   jsonb_strip_nulls(to_jsonb(properties) - 'way')
        //         ) AS feature
        //         FROM (
        //             SELECT *
        //             FROM )" + table + R"(
        //             WHERE )" + table + R"(.way && ST_Transform(
        //                 ST_MakeEnvelope()" +
        //                     bboxToQueryString(bbox) + ", " +
        //                     srid_out_s + "), " +
        //                 srid_in_s +
        //             R"()
        //             AND way_area > )" + std::to_string(darea.min) + R"(
        //             AND way_area < )" + std::to_string(darea.max) + R"(
        //         ) AS properties
        //     ) AS features
        //     LIMIT 10000;
        // )";
        // }

        // static std::string BBOXtoGeoJson(const std::string& table,
        //                                 const bbox_s& bbox,
        //                                 int srid_out,
        //                                 int srid_in)
        // {
        // std::string srid_out_s = std::to_string(srid_out);
        // std::string srid_in_s = std::to_string(srid_in);

        // return R"(
        //     SELECT jsonb_build_object(
        //     'type',     'FeatureCollection',
        //     'features', jsonb_agg(features.feature)
        //     )
        //     FROM (
        //         SELECT jsonb_build_object(
        //             'type',         'Feature',
        //             'geometry',     ST_AsGeoJSON(ST_Transform(
        //                                     way, )" +
        //                                     srid_out_s +
        //                                 R"()
        //                             )::jsonb,
        //             'properties',   jsonb_strip_nulls(to_jsonb(properties) - 'way')
        //         ) AS feature
        //         FROM (
        //             SELECT *
        //             FROM )" + table + R"(
        //             WHERE )" + table + R"(.way && ST_Transform(
        //                 ST_MakeEnvelope()" +
        //                     bboxToQueryString(bbox) + ", " +
        //                     srid_out_s + "), " +
        //                 srid_in_s +
        //             ")" + std::string(R"(
        //         ) AS properties
        //     ) AS features
        //     LIMIT 10000;
        //     )");
        // }


        static std::string bboxToQueryString(const bbox_s& bbox)
        {
            return std::to_string(bbox.min_lon) + ", " +
                std::to_string(bbox.min_lat) + ", " +
                std::to_string(bbox.max_lon) + ", " +
                std::to_string(bbox.max_lat);
        }

        static std::string bboxAreaDraw(const std::string& table,
                                        const bbox_s& bbox,
                                        d_area_s darea,
                                        int srid_out)
        {
            return
                "SELECT " + 
                    DBDT::ID_COL + ", "
                    "ST_Transform(" + DBDT::WAY_COL + ", " + 
                        std::to_string(srid_out) +
                    ") AS "+ DBDT::WAY_WKB_COL + ", " +
                    // "ST_AsText(ST_Transform(way, " + 
                    //     std::to_string(srid_out) +
                    // ")),"
                    DBDT::DRAW_TYPE_COL +
                " FROM " + table +
                " WHERE " +
                    table + "." + DBDT::WAY_COL + " && ST_Transform("
                        "ST_MakeEnvelope(" +
                            bboxToQueryString(bbox) + ", " +
                            std::to_string(srid_out) +
                        "), " +
                        std::to_string(DBDT::SRID) +
                    ")"
                    " AND " + DBDT::WAY_AREA_COL + " > " + std::to_string(darea.min) +
                    " AND " + DBDT::WAY_AREA_COL + " < " + std::to_string(darea.max) +
                    " AND " + DBDT::DRAW_TYPE_COL + " >= 0"
                " LIMIT " + std::to_string(DBDT::LIMIT) + ";";

            // return
            //     "WITH geom_data AS ("
            //         "SELECT" 
            //             " osm_id,"
            //             " ST_Transform(way, " +
            //                  std::to_string(srid_out) +
            //             ") AS transformed_way,"
            //             " draw_type"
            //         " FROM" + table +
            //         " WHERE " +
            //             table + ".way && ST_Transform("
            //                 "ST_MakeEnvelope(" +
            //                     bboxToQueryString(bbox) + ", " +
            //                     std::to_string(srid_out) +
            //                 "), " +
            //                 std::to_string(srid_in) +
            //             ")"
            //             " AND way_area > " + std::to_string(darea.min) +
            //             " AND way_area < " + std::to_string(darea.max) +
            //             " AND draw_type >= 0"
            //         " LIMIT 10000"
            //     ")"
            //     " SELECT" 
            //         " osm_id,"
            //         " draw_type,"
            //         " ("
            //             "SELECT array_agg(ARRAY[ST_X(p.geom), ST_Y(p.geom)])"
            //             "FROM ST_DumpPoints(g.transformed_way) AS p"
            //         ") AS coordinates"
            //     " FROM geom_data g;";
        }
};

    // std::string query_1 = R"(
    //     SELECT *
    //     FROM planet_osm_roads
    //     WHERE planet_osm_roads.way && ST_Transform(
    //         ST_MakeEnvelope()" +
    //             bboxToQueryString(bbox) + ", " +
    //             std::to_string(srid_out) + "), " +
    //         std::to_string(srid_) +
    //     ");";

    // std::string query = R"(
    // SELECT jsonb_build_object(
    // 'type', 'FeatureCollection',
    // 'features', jsonb_agg(features.feature)
    // )
    // FROM (
    //     SELECT jsonb_build_object(
    //         'type', 'Feature',
    //         'geometry', ST_AsGeoJSON(ST_Transform(way, 4326))::jsonb,
    //         'properties', to_jsonb(properties) - 'way'
    //     ) AS feature
    //     FROM ()" + std::string(R"(
    //             SELECT *
    //             FROM planet_osm_roads
    //             WHERE planet_osm_roads.way && ST_Transform(
    //                 ST_MakeEnvelope()" +
    //                     bboxToQueryString(bbox) + ", " +
    //                     std::to_string(srid_out) + "), " +
    //                 std::to_string(srid_) +
    //             ")") + std::string(R"(
    //     ) AS properties
    // ) AS features;
    // )");


} // namespace maykitbo::maps