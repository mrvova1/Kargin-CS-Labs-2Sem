#pragma once
#include <vector>
#include <tuple>
#include <unordered_map>

class CollaborativeModel {
public:
    using SimilarUser = std::tuple<int, double, std::vector<int>>; // id, similarity, likedItems

    CollaborativeModel(const std::vector<SimilarUser>& users);
    std::vector<std::pair<int,double>> score() const;

private:
    std::vector<SimilarUser> users_;
};
