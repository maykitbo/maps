#pragma once


#include <vector>

#include "types.h"


namespace maykitbo::maps
{


template
<
    class way_conteiner,
    class coords_preprocess,
    class ItemTypes
>
class Feature
{
    public:
        Feature() = default;
        void parse(idx_t idx, const char* wkb, ItemTypes draw_type);

        idx_t idx() const
            { return idx_; }
        const way_conteiner& coordinates() const
            { return coordinates_; }
        way_conteiner& coordinates()
            { return coordinates_; }
        ItemTypes type() const
            { return type_; }

    private:

        idx_t idx_;
        way_conteiner coordinates_;
        ItemTypes type_;

        using wkb_int = int16_t;
        using wkb_hex_int = int8_t;
        using wkb_fp = double;

        const static wkb_int SIZE_IDX = 13;
        const static wkb_int LON_IDX = 4; // after size shift
        const static wkb_int WKBFP_LEN = sizeof(wkb_fp);
        const static wkb_int LAT_IDX = LON_IDX + WKBFP_LEN;
        const static wkb_int COORD_STEP = WKBFP_LEN * 2;

        void parseWKB(const char* wkb);
};


template
<class way_conteiner, class coords_preprocess, class ItemTypes>
void Feature<way_conteiner, coords_preprocess, ItemTypes>
::parse(idx_t idx, const char* wkb, ItemTypes draw_type)
{
    idx_ = idx;
    parseWKB(wkb);
    type_ = draw_type;
}


template
<class way_conteiner, class coords_preprocess, class ItemTypes>
void Feature<way_conteiner, coords_preprocess, ItemTypes>
::parseWKB(const char* wkb)
{
    std::string binaryData;

    for (const char *w = wkb + 2 * SIZE_IDX;
        *w != '\0' && *(w + 1) != '\0';
        w += 2)
    {
        int8_t c = 0;
        sscanf(w, "%2hhx", &c);
        binaryData += static_cast<char>(c);
    }

    wkb_int size = *(wkb_int*)&binaryData[0];
    coordinates_.resize(size);

    for (int16_t k = 0, lat_i = LAT_IDX, lon_i = LON_IDX;
        k < size && lat_i < binaryData.size();
        ++k, lat_i += COORD_STEP, lon_i += COORD_STEP)
    {
        coordinates_[k] = coords_preprocess::act(
                *reinterpret_cast<double*>(&binaryData[lat_i]),
                *reinterpret_cast<double*>(&binaryData[lon_i])
        );
    }
}


} // namespace maykitbo::maps
