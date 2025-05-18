#pragma once
#include "UserProfile.hpp"
#include <vector>
#include <unordered_map>

class ContentModel {
public:
    using Item = std::pair<int, std::vector<int>>; // itemId, tagIds

    std::vector<std::pair<int, double>> score(
        const UserProfile& user,
        const std::vector<Item>& items) const;
};
