#include "ContentModel.hpp"
#include <cmath>
#include <algorithm>

std::vector<std::pair<int, double>> ContentModel::score(
    const UserProfile& user,
    const std::vector<Item>& items) const
{
    std::vector<std::pair<int, double>> result;
    for (auto& item : items) {
        double dot = 0.0, normItem = 0.0, normUser = 0.0;
        for (int tagId : item.second) {
            double uw = user.weight(tagId);
            dot += uw * uw;
            normItem += uw * uw;
            normUser += uw * uw;
        }
        double sim = (normItem > 0 && normUser > 0) ? dot / std::sqrt(normItem * normUser) : 0.0;
        result.emplace_back(item.first, sim);
    }
    std::sort(result.begin(), result.end(),
              [](auto& a, auto& b){ return a.second > b.second; });
    return result;
}
