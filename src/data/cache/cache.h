#pragma once


#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <unordered_map>
#include <vector>

#include "types.h"

namespace maykitbo::maps
{


template<class F>
class CachedFeature
{
    private:
        F feature_;
        bbox_s bbox_;
};


// Assuming your feature class 'F' has a method to get its geometry or bounding box.
template<class F>
class FeaturesCache {
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

public:
    FeaturesCache(size_t capacity) : capacity_(capacity) {}

    // Insert a feature into the cache
    void put(const idx_t& key, const F& feature) {
        if (cache_map_.size() >= capacity_) {
            // Evict logic here (e.g., based on LFU or LRU)
            // For spatial cache, you need to also remove from the spatial index
            evictFeature();
        }
        cache_map_[key] = feature;

        // Insert the feature's bounding box into the spatial index
        auto box = feature.getBoundingBox(); // Assuming this method exists
        rtree_.insert(std::make_pair(box, key));
    }

    // Get features within a bounding box
    std::vector<F> getFeaturesInBox(const BoundingBox& query_box) {
        std::vector<F> result_features;

        // Query the spatial index
        std::vector<std::pair<BoundingBox, idx_t>> query_result;
        rtree_.query(bgi::intersects(query_box), std::back_inserter(query_result));

        // Retrieve the features from the cache map
        for (const auto& pair : query_result) {
            const idx_t& key = pair.second;
            result_features.push_back(cache_map_[key]);
        }

        return result_features;
    }

    // Check if a feature is in the cache
    bool contains(const idx_t& key) const {
        return cache_map_.find(key) != cache_map_.end();
    }

    // Remove a feature from the cache (used during eviction)
    void remove(const idx_t& key) {
        auto it = cache_map_.find(key);
        if (it != cache_map_.end()) {
            auto box = it->second.getBoundingBox();
            rtree_.remove(std::make_pair(box, key));
            cache_map_.erase(it);
        }
    }

private:
    void evictFeature() {
        // Implement your eviction logic here
        // For example, remove the least frequently used feature
        // Make sure to remove it from both cache_map_ and rtree_
    }

    size_t capacity_;
    std::unordered_map<idx_t, F> cache_map_; // Map of features
    bgi::rtree<std::pair<BoundingBox, idx_t>, bgi::quadratic<16>> rtree_; // Spatial index
};


} // namespace maykitbo::maps
