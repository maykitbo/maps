#pragma once

#include "../osm_data/osm_parser/parser.h"
#include "../settings/constants.h"

#include <vector>

namespace maykitbo::maps {


struct Algebra
{
    static coord_t toRadians(coord_t degree);
    static rlen_t distanse(coord_t lat1, coord_t lon1, coord_t lat2, coord_t lon2);
};


} // namespace maykitbo::maps