#pragma once

#include <sstream>
#include <vector>

#include "pqxx/pqxx"


#include "types.h"
#include "structure.h"


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


template<class way_conteiner, class coords_preprocess>
struct WKBParser
{
    static way_conteiner read(const char* text);

    static way_conteiner parse(const char* wkb);
};


template<class way_conteiner, class coords_preprocess>
class Feature
{
    using DBDT = db::DBStruct;

    public:
        // Feature() = default;
        void parse(const pqxx::row& feature)
        {
            idx_ = feature[DBDT::ID_COL].as<idx_t>();
            coordinates_ = std::move(
                WKBParser<way_conteiner, coords_preprocess>::read(
                    feature[DBDT::TEXT_WAY_COL].c_str()));
        }
        

        idx_t idx() const
            { return idx_; }
        const way_conteiner& coordinates() const
            { return coordinates_; }
        // way_conteiner& coordinates()
        //     { return coordinates_; }

    protected:

        idx_t idx_;
        way_conteiner coordinates_;
};


template<class way_conteiner, class coords_preprocess, class ItemTypes>
class DrawFeature : public Feature<way_conteiner, coords_preprocess>
{
    using DBDT = db::DBStruct;
    using F =  Feature<way_conteiner, coords_preprocess>;
    public:
        void parse(const pqxx::row& feature)
        {
            F::idx_ = feature[DBDT::ID_COL].as<idx_t>();
            F::coordinates_ = std::move(
                WKBParser<way_conteiner, coords_preprocess>::read(
                    feature[DBDT::TEXT_WAY_COL].c_str()));
            type_ = static_cast<ItemTypes>(feature[DBDT::DRAW_TYPE_COL].as<int>());
        }

        ItemTypes type() const
            { return type_; }

    private:
        ItemTypes type_;
};


// template<class way_conteiner, class coords_preprocess, class ItemTypes>
// class Feature
// {
//     using DBDT = db::DBStruct;

//     public:
//         void parse(const pqxx::row& feature)
//         {
//             idx_ = feature[DBDT::ID_COL].as<idx_t>();
//             coordinates_ = std::move(
//                 WKBParser<way_conteiner, coords_preprocess>::read(
//                     feature[DBDT::TEXT_WAY_COL].c_str()));
                    
//             type_ = static_cast<ItemTypes>(feature[DBDT::DRAW_TYPE_COL].as<int>());
//         }
//         ItemTypes type() const
//             { return type_; }
        
//         idx_t idx() const
//             { return idx_; }
//         const way_conteiner& coordinates() const
//             { return coordinates_; }
//         way_conteiner& coordinates()
//             { return coordinates_; }

//     private:

//         ItemTypes type_;
//         idx_t idx_;
//         way_conteiner coordinates_;
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

template<class way_conteiner, class coords_preprocess>
way_conteiner WKBParser<way_conteiner, coords_preprocess>::parse(const char* wkb)
{
    static const u_int8_t SIZE_IDX = 13;

    way_conteiner coordinates;
    
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
        coordinates[k] = coords_preprocess::act(
            *reinterpret_cast<double*>(binary_data + sizeof(double)),
            *reinterpret_cast<double*>(binary_data)
        );
    }

    return coordinates;
}


template<class way_conteiner, class coords_preprocess>
way_conteiner WKBParser<way_conteiner, coords_preprocess>::read(const char* text)
{
    std::stringstream ss(text);
    way_conteiner way;
    
    
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
        way.push_back(coords_preprocess::act(lat, lon));
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
