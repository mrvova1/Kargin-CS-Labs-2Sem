#pragma once
#include "ContentModel.hpp"
#include "CollaborativeModel.hpp"
#include "GraphModel.hpp"
#include "RLModel.hpp"
#include "UserProfile.hpp"
#include <unordered_map>
#include <vector>
#include <string>

class RecommenderEngine {
public:
    RecommenderEngine(const std::string& configPath);

    std::vector<int> recommend(
        const UserProfile& user,
        const ContentModel& content,
        const CollaborativeModel& collab,
        const GraphModel& graph,
        const RLModel& rl,
        const std::vector<ContentModel::Item>& items,
        int K);

private:
    void loadConfig(const std::string& path);

    double tailFraction_, temperature_, alpha_;
    bool useGraph_, useRL_;
};
