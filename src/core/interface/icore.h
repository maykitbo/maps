#pragma once


#include "data_manager.h"
#include "types.h"


namespace maykitbo::maps
{


class ICore
{
    public:
        ICore() = default;
        ~Icore();

        void setData(DataManager* data);

        route_s createRoute(node_id from, node_id to);
        distance_t measureDistance(point_s from, point_s to);

    private:
        DataManager* data_;
}



} // namespace maykitbo::maps
