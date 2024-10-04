#pragma once

#include <sstream>
#include <vector>

#include "pqxx/pqxx"


#include "types.h"
#include "structure.h"
#include "idata.h"


namespace maykitbo::maps
{


template<class Point>
struct CoordPreprocess
{
    static Point act(double lat, double lon)
    {
        return Point{lat, lon};
    }
};


template<class Way, class CPrep>
struct WKBParser
{
    static Way read(const char* text);

    static Way parse(const char* wkb);
};


template<class Way, class CPrep>
class Feature
{
    protected:
        using DBDT = db::DBStruct;

    public:
        // Feature() = default;
        void parse(const pqxx::row& feature)
        {
            idx_ = feature[DBDT::ID_COL].as<idx_t>();
            coordinates_ = std::move(
                WKBParser<Way, CPrep>::read(
                    feature[DBDT::PROJECTED_WAY].c_str()));
            parseOtherCols(feature);
        }

        idx_t idx() const
            { return idx_; }
        const Way& coordinates() const
            { return coordinates_; }

    protected:
        virtual void parseOtherCols(const pqxx::row& feature) {}

        idx_t idx_;
        Way coordinates_;
};


template<class ItemTypes>
class DrawTypeFeature : public Feature<std::vector<point_s>, CoordPreprocess<point_s>>
{
    public:
        ItemTypes type() const
            { return type_; }

    private:
        ItemTypes type_;

        void parseOtherCols(const pqxx::row& feature) override
        {
            type_ = static_cast<ItemTypes>(feature[DBDT::DRAW_TYPE_COL].as<int>());
        }
};


class LineFeature : public DrawTypeFeature<LineTypes> {};

class RoadFeature : public DrawTypeFeature<LineTypes> {};

class PointFeature : public Feature<std::vector<point_s>, CoordPreprocess<point_s>> {};



class PolygonFeature : public Feature<std::vector<point_s>, CoordPreprocess<point_s>>
{
    public:
        coord_t wayArea() const { return way_area_; }
        PolygonTypes type() const { return type_; }
    private:
        PolygonTypes type_;
        coord_t way_area_;

        void parseOtherCols(const pqxx::row& feature) override
        {
            // std::cout << feature["raw_way"].c_str() << "\n";
            // auto coords = WKBParser<std::vector<point_s>, CoordPreprocess<point_s>>::read(
            //         feature["raw_way"].c_str());
            // for (auto c : coords)
            // {
            //     std::cout << c.lat << ' ' << c.lon << "; ";
            // }
            // std::cout << "\n\n";

            type_ = static_cast<PolygonTypes>(feature[DBDT::DRAW_TYPE_COL].as<int>());
            way_area_ = feature[DBDT::WAY_AREA_COL].as<double>();
        }
};



// class LineFeature : public Feature<std::vector<point_s>, CoordPreprocess<point_s>>
// {
//     private:
//         PolygonTypes type_;

//         void parseOtherCols(const pqxx::row& feature) override
//         {
//             type_ = static_cast<PolygonTypes>(feature[DBDT::DRAW_TYPE_COL].as<int>());
//             way_area_ = feature[DBDT::WAY_AREA_COL].as<double>();
//         }
// };


// template<class Way, class CPrep, class ItemTypes>
// class DrawFeature : public Feature<Way, CPrep>
// {
//     using DBDT = db::DBStruct;
//     using F =  Feature<Way, CPrep>;
//     public:
//         void parse(const pqxx::row& feature)
//         {
//             F::idx_ = feature[DBDT::ID_COL].as<idx_t>();
//             F::coordinates_ = std::move(
//                 WKBParser<Way, CPrep>::read(
//                     feature[DBDT::TEXT_WAY_COL].c_str()));
//             type_ = static_cast<ItemTypes>(feature[DBDT::DRAW_TYPE_COL].as<int>());
//         }

//         ItemTypes type() const
//             { return type_; }

//     private:
//         ItemTypes type_;
// };


// template<class Way, class CPrep, class ItemTypes>
// class Feature
// {
//     using DBDT = db::DBStruct;

//     public:
//         void parse(const pqxx::row& feature)
//         {
//             idx_ = feature[DBDT::ID_COL].as<idx_t>();
//             coordinates_ = std::move(
//                 WKBParser<Way, CPrep>::read(
//                     feature[DBDT::TEXT_WAY_COL].c_str()));
                    
//             type_ = static_cast<ItemTypes>(feature[DBDT::DRAW_TYPE_COL].as<int>());
//         }
//         ItemTypes type() const
//             { return type_; }
        
//         idx_t idx() const
//             { return idx_; }
//         const Way& coordinates() const
//             { return coordinates_; }
//         Way& coordinates()
//             { return coordinates_; }

//     private:

//         ItemTypes type_;
//         idx_t idx_;
//         Way coordinates_;
// };


static void binaryPrint(const std::string& str)
{
    for (int k = 0; k < str.size(); ++k)
    {
        for (int i = 7; i >= 0; --i)
        {
            std::cout << ((((*(u_int8_t*)(&str[k]) << i) & 1) == 0) ? '0' : '1');
        }
        std::cout << ' ';
    }
    std::cout << '\n';
}

template<class Way, class CPrep>
Way WKBParser<Way, CPrep>::parse(const char* wkb)
{
    static const u_int8_t SIZE_IDX = 13;

    Way coordinates;
    
    u_int32_t size = 0;
    for (u_int8_t k = 2 * (SIZE_IDX + sizeof(u_int32_t) - 1), i = 3;
        k >= 2 * SIZE_IDX;
        k -= 2, --i)
    {
        u_int8_t c = 0;
        sscanf(&wkb[k], "%2hhx", &c);
        size += c << i * 8;
    }

    coordinates.resize(size);


    u_int8_t pair_len = 2 * sizeof(double) / sizeof(char);
    char binary_data[pair_len];

    for (u_int32_t k = 0; k < size; ++k)
    {
        for (u_int8_t i = 0; i < pair_len; ++i)
        {
            sscanf(
                wkb + 2 * ((SIZE_IDX + 4) + k * pair_len + i),
                "%2hhx", binary_data + i);
        }
        coordinates[k] = CPrep::act(
            *reinterpret_cast<double*>(binary_data + sizeof(double)),
            *reinterpret_cast<double*>(binary_data)
        );
    }

    return coordinates;
}


template<class Way, class CPrep>
Way WKBParser<Way, CPrep>::read(const char* text)
{
    std::stringstream ss(text);
    Way way;
    
    
    ss.ignore(128, '(');
    // while (ss.peek() != '(')
    //     ss.ignore(1);
    while (ss.peek() == '(')
        ss.ignore(1);

    while (ss && ss.peek() != ')')
    {
        double lat, lon;
        ss >> lon;
        ss >> lat;
        way.push_back(CPrep::act(lat, lon));
        if (ss.peek() == ')')
            break;
        ss.ignore(1);
    }

    // std::string SSS(text);
    // if (SSS.size() < 60)
    // {
    //     std::cout << SSS << "\n";
    //     for (auto point : way)
    //     {
    //         std::cout << point.x() << ' ' << point.y() << ' ';
    //     }
    //     std::cout << "\n";
    // }

    return way;
}


} // namespace maykitbo::maps
