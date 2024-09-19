#pragma once


#include "feature.h"
#include "pqxx/pqxx"


namespace maykitbo::maps
{


template
<
    class way_conteiner,
    class coords_preprocess,
    class ItemTypes
>
class FeatureSet
{
    public:
        using F = Feature<way_conteiner, coords_preprocess, ItemTypes>;

        FeatureSet() = default;

        // void fetch(const bbox_s& bbox, d_area_s darea, int srid = 4326);
        // void forEach(const std::function<void(const F&)>& func);
        void parse(const pqxx::result& pqxx_data);

        std::vector<F>::const_iterator begin() const
            { return data_.begin(); }
        std::vector<F>::const_iterator end() const
            { return data_.end(); }

    private:
        std::vector<F> data_;
};


// template
// <class way_conteiner, class coords_preprocess, class ItemTypes>
// void FeatureSet<way_conteiner, coords_preprocess, ItemTypes>
// ::fetch(const bbox_s& bbox, d_area_s darea, int srid)
// {
//     PostGISConnector pgc;
//     pqxx::result R = pgc.fetchDraw(
//         DBStruct::POLYGON_TABLE, bbox, darea, srid);
//     parse(R);
// }


template
<class way_conteiner, class coords_preprocess, class ItemTypes>
void FeatureSet<way_conteiner, coords_preprocess, ItemTypes>
::parse(const pqxx::result& pqxx_data)
{
    data_.reserve(pqxx_data.size());
    for (const pqxx::row& feature : pqxx_data)
    {
        data_.push_back(Feature{});                
    
        data_.back().parse
        (
            feature[DBStruct::ID_COL].as<idx_t>(),
            feature[DBStruct::WAY_WKB_COL].c_str(),
            static_cast<PolygonTypes>(feature[DBStruct::DRAW_TYPE_COL].as<int>())
        );
    }
    auto i = data_.begin();
}


} // namespace maykitbo::maps

