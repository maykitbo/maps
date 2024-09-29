#pragma once


#include "types/line.h"
#include "types/polygon.h"
#include "features/set.h"
#include "postgis_connector.h"

#include <unordered_map>
#include <list>


namespace maykitbo::maps
{


template<class F>
class FeaturesCache
{
    public:
        // Constructor to initialize the cache with a given capacity
        FeaturesCache(size_t capacity)
            : capacity_(capacity), min_freq_(0) {}

        // Function to get a feature by its index
        // Returns a pointer to the feature if found, or nullptr if not in cache
        F* get(const idx_t& key)
        {
            auto it = cache_entries_.find(key);
            if (it == cache_entries_.end())
            {
                return nullptr; // Feature not found in cache
            }
            // Update the frequency of the accessed feature
            increaseFrequency(it);
            return &(it->second.value);
        }

        // Function to insert or update a feature in the cache
        void put(const idx_t& key, const F& value)
        {
            if (capacity_ == 0)
            {
                return; // Cache capacity is zero, cannot store any features
            }

            auto it = cache_entries_.find(key);
            if (it != cache_entries_.end())
            {
                // Feature already exists in cache, update its value and frequency
                it->second.value = value;
                std::cout << "ERROR CAHCE IN MY LOGIC, CHECK!!!\n";
                increaseFrequency(it);
            }
            else
            {
                // If cache is full, remove the least frequently used feature
                if (cache_entries_.size() >= capacity_)
                {
                    // Find the feature to evict: oldest feature with the lowest frequency
                    const idx_t& key_to_evict = freq_lists_[min_freq_].back();
                    // Remove it from the cache entries
                    cache_entries_.erase(key_to_evict);
                    // Remove it from the frequency list
                    freq_lists_[min_freq_].pop_back();
                    if (freq_lists_[min_freq_].empty())
                    {
                        freq_lists_.erase(min_freq_);
                    }
                }
                // Insert the new feature with frequency count 1
                min_freq_ = 1;
                freq_lists_[min_freq_].push_front(key);
                cache_entries_[key] = {value, min_freq_, freq_lists_[min_freq_].begin()};
            }
        }

    private:
        // Internal representation of a cache entry
        struct CacheEntry
        {
            F value;  // The feature data
            int freq; // Access frequency count
            // Iterator to the position in the frequency list
            typename std::list<idx_t>::iterator freq_list_it;
        };

        // Function to update the frequency of a cache entry
        void increaseFrequency(typename std::unordered_map<idx_t, CacheEntry>::iterator it)
        {
            int freq = it->second.freq;
            // Remove the entry from the current frequency list
            freq_lists_[freq].erase(it->second.freq_list_it);

            // If the current frequency list is empty and it's the minimum frequency,
            // increment the minimum frequency
            if (freq_lists_[freq].empty())
            {
                freq_lists_.erase(freq);
                if (freq == min_freq_)
                {
                    min_freq_++;
                }
            }

            // Increase the frequency count
            freq++;
            // Add the entry to the new frequency list
            freq_lists_[freq].push_front(it->first);
            // Update the cache entry with new frequency and iterator
            it->second.freq = freq;
            it->second.freq_list_it = freq_lists_[freq].begin();
        }

        size_t capacity_; // Maximum capacity of the cache
        int min_freq_;    // Current minimum frequency in the cache

        // Hash map to store cache entries for fast lookup by key
        std::unordered_map<idx_t, CacheEntry> cache_entries_;

        // Hash map to store lists of keys for each frequency
        // Each frequency maps to a list of keys that have that access frequency
        std::unordered_map<int, std::list<idx_t>> freq_lists_;
    };



class IData
{
    public:
        IData(const std::string& conn_str)
            : pgc_(conn_str) {}

        template<class way_conteiner, class coords_preprocess>
        FeatureSet<way_conteiner, coords_preprocess, PolygonTypes>
        fethPolygons(const bbox_s& bbox, const d_area_s& darea, int limit = 10000) const;

        template<class way_conteiner, class coords_preprocess>
        FeatureSet<way_conteiner, coords_preprocess, LineTypes>
            fethLines(const bbox_s& bbox, int min_draw_type, int limit = 10000) const;

        const PostGISConnector& connector()
            { return pgc_; }
        
        std::string polygonInfoAsString(idx_t id) const
        {
            pqxx::result R = pgc_.getInfoById(DBStruct::POLYGON_TABLE, id);
            std::string info;
            for (const auto& r : R[0])
            {
                if (!r.is_null())
                {
                    info += std::string(r.name()) + " = " + r.c_str() + "\n";
                }
            }
            return info;
        }

    private:
        PostGISConnector pgc_;
};


// std::string IData::polygonInfoAsString(idx_t id) const
// {

// }


template<class way_conteiner, class coords_preprocess>
FeatureSet<way_conteiner, coords_preprocess, PolygonTypes>
IData::fethPolygons(const bbox_s& bbox, const d_area_s& darea, int limit) const
{
    pqxx::result R = pgc_.fetchBboxDarea(
        DBStruct::POLYGON_TABLE, bbox, darea, limit);
    
    FeatureSet<way_conteiner, coords_preprocess, PolygonTypes> polygons;
    polygons.parse(R);
    return polygons;
}


template<class way_conteiner, class coords_preprocess>
FeatureSet<way_conteiner, coords_preprocess, LineTypes>
IData::fethLines(const bbox_s& bbox, int min_draw_type, int limit) const
{
    pqxx::result R = pgc_.fetchBboxMinDrawType(
        DBStruct::LINE_TABLE, bbox, min_draw_type, limit);
    
    FeatureSet<way_conteiner, coords_preprocess, LineTypes> polygons;
    polygons.parse(R);
    return polygons;
}


} // namespace maykitbo::maps