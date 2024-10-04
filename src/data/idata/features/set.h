#pragma once



#include "feature.h"
#include "idata.h"
#include "pqxx/pqxx"
#include "structure.h"

#include <set>


namespace maykitbo::maps
{


template<class Set, class F>
class FeatureSetMeta
{
    public:
        void parse(const pqxx::result& pqxx_data)
        {
            data_.reserve(pqxx_data.size());
            for (const pqxx::row& feature : pqxx_data)
            {
                // data_.push_back(F{});          
                // data_.back().parse(feature);
                F f{};
                f.parse(feature);
                data_.insert(std::move(f));
                // insertFeature(feature);
            }
            auto i = data_.begin();
        }

        typename Set::iterator begin()
            { return data_.begin(); }
        typename Set::iterator end()
            { return data_.end(); }

        typename Set::const_iterator begin() const
            { return data_.cbegin(); }
        typename Set::const_iterator end() const
            { return data_.cend(); }
        
        size_t size() const
            { return data_.size(); }
    
    protected:
        Set data_;
};


struct PolygonComp
{
    bool operator()(const PolygonFeature& x, const PolygonFeature& y) const
    {
        return x.wayArea() > y.wayArea();
    }
};


class PolygonSet : public FeatureSetMeta<std::set<PolygonFeature, PolygonComp>, PolygonFeature>
{
    public:
        void parse(const pqxx::result& pqxx_data)
        {
            for (const pqxx::row& feature : pqxx_data)
            {
                PolygonFeature f{};
                f.parse(feature);
                data_.insert(std::move(f));
            }
            auto i = data_.begin();
        }
};

class LineSet : public FeatureSetMeta<std::vector<LineFeature>, LineFeature>
{
    public:
        void parse(const pqxx::result& pqxx_data)
        {
            data_.reserve(pqxx_data.size());
            for (const pqxx::row& feature : pqxx_data)
            {
                data_.push_back(LineFeature{});          
                data_.back().parse(feature);
            }
            auto i = data_.begin();
        }
};

class RoadSet : public FeatureSetMeta<std::vector<RoadFeature>, RoadFeature>
{
    public:
        void parse(const pqxx::result& pqxx_data)
        {
            data_.reserve(pqxx_data.size());
            for (const pqxx::row& feature : pqxx_data)
            {
                data_.push_back(RoadFeature{});          
                data_.back().parse(feature);
            }
            auto i = data_.begin();
        }
};

class PointSet : public FeatureSetMeta<std::vector<PointFeature>, PointFeature>
{
    public:
        void parse(const pqxx::result& pqxx_data)
        {
            data_.reserve(pqxx_data.size());
            for (const pqxx::row& feature : pqxx_data)
            {
                data_.push_back(PointFeature{});          
                data_.back().parse(feature);
            }
            auto i = data_.begin();
        }
};




// template<class Set>
// class FeatureSet :
//     public FeatureSetMeta<Set>
// {};


// template<class Set>
// class DrawFeatureSet :
//     public FeatureSetMeta<Set>
// {};


// template<class Way, class CPrep, class ItemTypes>
// class FeatureSet
// {
//     private:
//         using F = Feature<Way, CPrep, ItemTypes>;
//         std::vector<F> data_;

//     public:

//         FeatureSet() = default;

//         void parse(const pqxx::result& pqxx_data);

//         typename std::vector<F>::iterator begin()
//             { return data_.begin(); }
//         typename std::vector<F>::iterator end()
//             { return data_.end(); }

//         typename std::vector<F>::const_iterator begin() const
//             { return data_.cbegin(); }
//         typename std::vector<F>::const_iterator end() const
//             { return data_.cend(); }
        
//         size_t size() const
//             { return data_.size(); }
// };



// template
// <class Way, class CPrep, class ItemTypes>
// void FeatureSet<Way, CPrep, ItemTypes>
// ::parse(const pqxx::result& pqxx_data)
// {
//     data_.reserve(pqxx_data.size());
//     for (const pqxx::row& feature : pqxx_data)
//     {
//         data_.push_back(F{});                

//         data_.back().parse(feature);
//         // data_.back().parse
//         // (
//         //     feature[DBStruct::ID_COL].as<idx_t>(),
//         //     // feature[DBStruct::WAY_WKB_COL].c_str(),
//         //     feature[DBStruct::TEXT_WAY_COL].c_str(),
//         //     static_cast<ItemTypes>(feature[DBStruct::DRAW_TYPE_COL].as<int>())
//         // );
//     }
//     auto i = data_.begin();
// }


} // namespace maykitbo::maps

