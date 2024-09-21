#pragma once


#include "feature.h"
#include "pqxx/pqxx"
#include "database_structure.h"


namespace maykitbo::maps
{


template<class way_container, class coords_preprocess, class ItemTypes>
class FeatureSet
{
    private:
        using F = Feature<way_container, coords_preprocess, ItemTypes>;
        std::vector<F> data_;

    public:

        FeatureSet() = default;

        void parse(const pqxx::result& pqxx_data);

        typename std::vector<F>::iterator begin()
            { return data_.begin(); }
        typename std::vector<F>::iterator end()
            { return data_.end(); }

        typename std::vector<F>::const_iterator begin() const
            { return data_.cbegin(); }
        typename std::vector<F>::const_iterator end() const
            { return data_.cend(); }
        
        size_t size() const
            { return data_.size(); }
};



template
<class way_container, class coords_preprocess, class ItemTypes>
void FeatureSet<way_container, coords_preprocess, ItemTypes>
::parse(const pqxx::result& pqxx_data)
{
    data_.reserve(pqxx_data.size());
    for (const pqxx::row& feature : pqxx_data)
    {
        data_.push_back(F{});                
    
        data_.back().parse
        (
            feature[DBStruct::ID_COL].as<idx_t>(),
            // feature[DBStruct::WAY_WKB_COL].c_str(),
            feature[DBStruct::TEXT_WAY_COL].c_str(),
            static_cast<ItemTypes>(feature[DBStruct::DRAW_TYPE_COL].as<int>())
        );
    }
    auto i = data_.begin();
}


} // namespace maykitbo::maps

