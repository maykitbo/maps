#include "matrix_graph.h"


using namespace maykitbo::maps;


MatrixGraph::MatrixGraph(const json_t& data)
    : data_(data)
{
    for (const auto& feature : OsmParser::getFeatures(data_))
    {
        if (OsmParser::isNode(feature))
        {
            matrix_ids_[OsmParser::getId(feature)] = node_ids_.size();
            node_ids_.push_back(OsmParser::getId(feature));
        }
    }

    size_ = node_ids_.size();
    matrix_.resize(size_ * size_);

    for (const auto& feature : OsmParser::getFeatures(data_))
    {
        if (OsmParser::isWay(feature))
        {
            auto iter = OsmParser::getNodes(feature).begin();

            for (fiat_idx_t node_id : OsmParser::getNodes(feature))
            {
                
            }
        }
    }
}

