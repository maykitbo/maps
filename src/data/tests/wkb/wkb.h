#pragma once


#include <iostream>
#include <vector>
#include <sstream>

#include "database_manager/postgis_connector.h"
#include "config.h"
#include "idata/features/feature.h"

#include "time_test.h"


using namespace maykitbo::maps;


struct WKB
{
    using DBDT = DBStruct;
    using Point = std::pair<double, double>;
    using Set = std::vector<Point>;

    static const int fail_output_range = 2;
    inline static const bbox_s bbox{55.816, 55.81, 37.667, 37.655};
    static const int limit_per_table = 2;

    static pqxx::result getWKBData(const std::string& table)
    {
        PostGISConnector pgc(Conf::postgis);
        return pgc.executeNonTransactionalQuery
        (
            "SELECT "
                "ST_Transform(" + DBDT::WAY_COL + ", " + 
                    std::to_string(DBDT::SRID_OUT) +
                ") AS wkb_way " +
            " FROM " + table +
            " WHERE " +
                table + "." + DBDT::WAY_COL + " && ST_Transform("
                    "ST_MakeEnvelope(" +
                        PostGisQuery::bboxToQueryString(bbox) + ", " +
                        std::to_string(DBDT::SRID_OUT) +
                    "), " +
                    std::to_string(DBDT::SRID_IN) +
                ")"
            " LIMIT " + std::to_string(limit_per_table) + ";"
        );
    }

    static pqxx::result getTextData(const std::string& table)
    {
        PostGISConnector pgc(Conf::postgis);
        return pgc.executeNonTransactionalQuery
        (
            "SELECT "
                "ST_AsText(ST_Transform(way, " + 
                    std::to_string(DBDT::SRID_OUT) +
                ")) AS text_way " + 
            " FROM " + table +
            " WHERE " +
                table + "." + DBDT::WAY_COL + " && ST_Transform("
                    "ST_MakeEnvelope(" +
                        PostGisQuery::bboxToQueryString(bbox) + ", " +
                        std::to_string(DBDT::SRID_OUT) +
                    "), " +
                    std::to_string(DBDT::SRID_IN) +
                ")"
            " LIMIT " + std::to_string(limit_per_table) + ";"
        );
    }

    static Set parseCoordText(const std::string& text_way)
    {
        std::cout << text_way << '\n';
        std::stringstream ss(text_way);
        Set set;
        ss.ignore(128, '(');
        while (ss.peek() == '(')
            ss.ignore(1);

        while (ss && ss.peek() != ')')
        {
            double lat, lon;
            ss >> lon;
            ss >> lat;
            std::cout << lat << ' ' << lon << '\n';
            set.push_back({lon, lat});
            if (ss.peek() == ')')
                break;
            ss.ignore(1);
        }
        return set;
    }

    static void printButch(const Set& expected, const Set& result, int k)
    {
        std::cout << "idx\tExpected\t\tResult\n";
        int start = k > fail_output_range ? k - fail_output_range / 2 : 0;
        for (int i = start;
            i < start + fail_output_range && (i < result.size() || i < expected.size());
            ++i)
        {
            if (i < expected.size())
                std::cout << i << "\t{" << expected[i].second << ", " << expected[i].first << "}";
            else
                std::cout << i << "\t\t\t";
            if (i < result.size())
                std::cout << "\t{" << result[i].first << ", " << result[i].second << "}\n";
            else
                std::cout << "\n";
        }
    }

    static void test(const std::string& table, double epsilon)
    {
        maykitbo::TimeTest overhead("overhead");

        maykitbo::TimeTest get_text_tt("get text data");
        pqxx::result Rtext = getTextData(table);
        get_text_tt.pause();

        maykitbo::TimeTest get_wkb_tt("get wkb data");
        pqxx::result Rwkb = getWKBData(table);
        get_wkb_tt.pause();

        maykitbo::TimeTest wkb_tt("wkb");
        maykitbo::TimeTest text_tt("text");

        bool k = false;
        for (int g = 0; g < Rtext.size(); ++ g)
        {
            wkb_tt.resume();
            Set result = WKBParser<Set, CoordPreprocess<Point>>::read(Rtext[g]["text_way"].c_str());
            wkb_tt.pause();

            text_tt.resume();
            Set expected = parseCoordText(Rtext[g]["text_way"].c_str());
            text_tt.pause();


            if (result.size() != expected.size())
            {
                std::cout << "Incorrect size: expected " << expected.size() << " != result " << result.size() << "\n";
                printButch(result, expected, std::min(result.size(), expected.size()));
            }
            else
            {
                for (int k = 0; k < result.size(); ++k)
                {
                    if (std::abs(result[k].first - expected[k].second) >= epsilon ||
                        std::abs(result[k].second - expected[k].first) >= epsilon)
                    {
                        std::cout << "Incorrect result in idx = " << k << "\n";
                        printButch(result, expected, k);
                        // std::cout << "\nWKB: " << r["wkb_way"].c_str() << "\n";
                        return;
                    }
                }
            }
        }
        overhead.pause();

        std::cout << overhead <<
                     get_text_tt <<
                     get_wkb_tt <<
                     text_tt <<
                     wkb_tt <<
                     get_text_tt + text_tt <<
                     get_wkb_tt + wkb_tt;

        std::cout << limit_per_table << " tests for table " << table << " DONE\n";
    }


    static void test()
    {
        // test(DBDT::POLYGON_TABLE, 0.001);
        test(DBDT::LINE_TABLE, 0.001);
    }
};


