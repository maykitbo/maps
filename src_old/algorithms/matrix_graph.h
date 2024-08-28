#pragma once


#include "algebra.h"

#include <vector>
#include <unordered_map>


namespace maykitbo::maps {


class MatrixGraph
{
    public:
        MatrixGraph(const json_t& data);

        feat_idx_t size() const { return size_; }
    
        void print();

    private:
        std::vector<feat_idx_t> node_ids_;
        std::unordered_map<feat_idx_t> matrix_ids_;
        std::vector<rlen_t> matrix_;
        const json_t& data_;
        feat_idx_t size_;

        rlen_t &cell(feat_idx_t row, feat_idx_t col)
            { return matrix_[row * size_ + col]; }
        const rlen_t &cell(feat_idx_t row, feat_idx_t col) const
            { return matrix_[row * size_ + col]; }

};


} // namespace maykitbo::maps
