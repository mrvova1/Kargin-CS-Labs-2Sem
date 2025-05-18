#pragma once
#include "TagGraph.hpp"
#include "UserProfile.hpp"
#include <vector>
#include <utility>

class GraphModel {
public:
    GraphModel(const TagGraph& graph);
    std::vector<std::pair<int,double>> score(
        const UserProfile& user,
        const std::vector<std::pair<int,std::vector<int>>>& items,
        size_t topNeighbors = 3) const;

private:
    const TagGraph& graph_;
};
