#pragma once


#include "types.h"


namespace maykitbo::maps
{
    

// level of detalisation
struct LoD
{
    static d_area_s maxMinArea(coord_t bbox_area)
    {
        return
        {
            bbox_area / 2000.0,
            bbox_area / 3.0
        };
    }
};


} // namespace maykitbo::maps