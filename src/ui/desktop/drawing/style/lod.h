#pragma once


#include <unordered_map>

#include "types.h"
#include "idata/types/line.h"


namespace maykitbo::maps
{
    

// level of detalisation
struct LoD
{
    static d_area_s maxMinArea(coord_t bbox_area)
    {
        return
        {
            bbox_area / 300.0,
            bbox_area / 1.0
        };
    }

    static float sparse(coord_t bbox_area)
    {
        if (bbox_area > 5e8)
            return 0.2;
        else if (bbox_area > 2.5e8)
            return 0.35;
        else if (bbox_area > 1e8)
            return 0.5;
        else if (bbox_area > 1e7)
            return 0.65;
        else if (bbox_area > 6e6)
            return 0.8;
        return 1.0;
    }

    static bool points(coord_t bbox_area)
    {
        return bbox_area > 1e7;
    }

    static const inline std::unordered_map<LineTypes, int> lines =
    {
        {L_ABANDONED,       10},
        {L_UNKNOWN_PATH,    100},
        {L_CONSTRUCTION,    200},
        {L_PATH,            300},
        {L_STEPS,           400},
        {L_SERVICE,         500},
        {L_TRANSPORT,       600},
        {L_CYCLEWAY,        700},
        {L_MOTORWAY,        800},
        {L_TRACK,           900},
        {L_RESIDENTIAL,     1000},
        {L_TERTIARY,        1100},
        {L_SECONDARY,       1200},
        {L_PRIMARY,         1300},
        {L_TRUNK,           1400}
    };

    static int minLineDrawType(coord_t bbox_area)
    {
        if (bbox_area > 5e8)
            return lines.find(L_SECONDARY)->second + 1;
        else if (bbox_area > 2.5e8)
            return lines.find(L_TERTIARY)->second + 1;
        else if (bbox_area > 1e8)
            return lines.find(L_RESIDENTIAL)->second + 1;
        else if (bbox_area > 1e7)
            return lines.find(L_TRACK)->second + 1;
        else if (bbox_area > 6e6)
            return lines.find(L_STEPS)->second + 1;

        return 0;
    }
};

/*
1.06983e+06 -- all
2.73861e+06 -- all
7.01022e+06 -- no path
*/


} // namespace maykitbo::maps