#include "GraphModel.hpp"
#include <algorithm>

GraphModel::GraphModel(const TagGraph& graph) : graph_(graph) {}

std::vector<std::pair<int,double>> GraphModel::score(
    const UserProfile& user,
    const std::vector<std::pair<int,std::vector<int>>>& items,
    size_t topNeighbors) const
{
    std::vector<std::pair<int,double>> result;
    for (const auto& [itemId, tags] : items) {
        double score = 0.0;
        for (int tag : tags) {
            auto neighbors = graph_.neighbors(tag, topNeighbors);
            for (const auto& [neighborId, sim] : neighbors) {
                score += user.weight(neighborId) * sim;
            }
        }
        result.emplace_back(itemId, score);
    }
    std::sort(result.begin(), result.end(),
              [](auto& a, auto& b){ return a.second > b.second; });
    return result;
}
