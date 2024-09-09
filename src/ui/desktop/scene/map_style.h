#pragma once


#include <QPen>

#include "types.h"


namespace maykitbo::maps
{


struct MapStyle
{
    const bbox_s init_bbox
        {55.816, 55.809, 37.667, 37.645};

    const int init_width = 1200;
    const QBrush apartments{Qt::yellow};
    const QBrush buildings{Qt::blue};
    const QPen basic_polygon{QBrush{Qt::magenta}, 2};
    const QPen basic_road{QBrush{Qt::white}, 3}; 
    const QPen basic_line{QBrush{Qt::green}, 2};
};



} // namespace maykitbo::maps