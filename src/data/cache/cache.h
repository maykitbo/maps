#pragma once


#include <boost/geometry.hpp>
#include <boost/geometry/indexing.hpp>
#include <boost/geometry/io/wkt/wkt.hpp>
#include <vector>
#include <map>

#include "types.h"

namespace maykitbo::maps
{


namespace bg = boost::geometry;
typedef bg::model::point<double, 2, bg::cs::cartesian> Point;
typedef bg::model::polygon<Point> Polygon;


template<class F>
struct CahceFeature
{
    F feature;
    int rating;
};


template<class F>
class PolygonCache {
    private:
        std::vector<Polygon> items_;
        bg::index::rtree<Polygon, bg::index::quadratic<bg::index::point_type<Polygon>::type>> index_;

    public:
        void addPolygon(const Polygon& poly) {
            polygons.push_back(poly);
            index.insert(std::make_pair(poly, bg::index::key<Point>(poly)));
        }

        std::vector<size_t> queryBox(const Point& min, const Point& max) {
            std::vector<size_t> result;
            bg::index::query(
                index,
                bg::index::intersects(bg::envelope(min, max)),
                std::back_inserter(result),
                bg::index::all_sides
            );
            return result;
        }
};



} // namespace maykitbo::maps
