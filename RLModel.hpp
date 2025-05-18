#pragma once
#include <vector>
#include <random>
#include <utility>

class RLModel {
public:
    RLModel(double epsilon);

    std::vector<std::pair<int,double>> score(
        const std::vector<std::pair<int,double>>& items) const;

private:
    double epsilon_;
    std::mt19937 gen_;
    std::uniform_real_distribution<> dist_;
};
