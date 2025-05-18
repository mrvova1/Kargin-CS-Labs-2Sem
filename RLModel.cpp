#include "RLModel.hpp"
#include <algorithm>

RLModel::RLModel(double epsilon)
    : epsilon_(epsilon), gen_(std::random_device{}()), dist_(0.0, 1.0) {}

std::vector<std::pair<int,double>> RLModel::score(
    const std::vector<std::pair<int,double>>& items) const
{
    std::mt19937 genCopy  = gen_;
    auto distCopy = dist_;

    std::vector<std::pair<int,double>> result = items;
    std::shuffle(result.begin(), result.end(), genCopy);

    for (auto& [id, score] : result) {
        if (distCopy(genCopy) < epsilon_)
            score *= distCopy(genCopy); // случайный explore
    }
    std::sort(result.begin(), result.end(),
              [](auto& a, auto& b){ return a.second > b.second; });
    return result;
}
