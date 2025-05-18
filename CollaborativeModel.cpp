#include "CollaborativeModel.hpp"
#include <algorithm>

CollaborativeModel::CollaborativeModel(const std::vector<SimilarUser>& users)
    : users_(users) {}

std::vector<std::pair<int,double>> CollaborativeModel::score() const {
    std::unordered_map<int, double> scoreMap;
    for (auto& [uid, sim, items] : users_) {
        for (int itemId : items)
            scoreMap[itemId] += sim;
    }
    std::vector<std::pair<int,double>> result(scoreMap.begin(), scoreMap.end());
    std::sort(result.begin(), result.end(),
              [](auto& a, auto& b){ return a.second > b.second; });
    return result;
}
