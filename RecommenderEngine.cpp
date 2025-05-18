#include "RecommenderEngine.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using json = nlohmann::json;

RecommenderEngine::RecommenderEngine(const std::string& configPath) {
    loadConfig(configPath);
}

void RecommenderEngine::loadConfig(const std::string& path) {
    std::ifstream in(path);
    json j;
    in >> j;
    tailFraction_ = j["tailFraction"];
    temperature_ = j["temperature"];
    alpha_ = j["alpha"];
    useGraph_ = std::find(j["experimentFlags"].begin(), j["experimentFlags"].end(), "useGraph") != j["experimentFlags"].end();
    useRL_ = std::find(j["experimentFlags"].begin(), j["experimentFlags"].end(), "useRL") != j["experimentFlags"].end();
}

std::vector<int> RecommenderEngine::recommend(
    const UserProfile& user,
    const ContentModel& content,
    const CollaborativeModel& collab,
    const GraphModel& graph,
    const RLModel& rl,
    const std::vector<ContentModel::Item>& items,
    int K)
{
    auto cRecs = content.score(user, items);
    auto gRecs = useGraph_ ? graph.score(user, items, 3) : cRecs;
    auto collabRecs = collab.score();

    std::unordered_map<int,double> combined;
    for (auto& [id, s] : gRecs) combined[id] += alpha_ * s;
    for (auto& [id, s] : collabRecs) combined[id] += (1.0 - alpha_) * s;

    // 1) собираем merged
    std::vector<std::pair<int,double>> merged(combined.begin(), combined.end());
    std::sort(merged.begin(), merged.end(),
              [](auto& a, auto& b){ return a.second > b.second; });

    // 2) рассчитываем core и tail
    int total = static_cast<int>(merged.size());
    int core  = static_cast<int>(K * (1.0 - tailFraction_));
    int tail  = K - core;

    // защита от выхода за границы:
    if (core > total) core = total;
    if (core < 0)    core = 0;
    if (tail < 0)    tail = 0;
    if (core + tail > total) {
        // недостаточно элементов: уменьшаем tail
        tail = total - core;
    }

    // 3) формируем финальный список
    std::vector<std::pair<int,double>> final;
    final.reserve(std::min(K, total));
    // Кор-элементы (топовые)
    for (int i = 0; i < core; ++i) {
        final.push_back(merged[i]);
    }
    // Остальные — рандомно из «хвоста»
    std::vector<std::pair<int,double>> tailSet(
        merged.begin() + core, merged.end());
    std::shuffle(tailSet.begin(), tailSet.end(), std::mt19937{std::random_device{}()});
    for (int i = 0; i < tail && i < static_cast<int>(tailSet.size()); ++i) {
        final.push_back(tailSet[i]);
    }

    // 4) при необходимости RL‑модель
    if (useRL_) {
        final = rl.score(final);
    }

    // 5) вычленяем только id и возвращаем
    std::vector<int> result;
    result.reserve(std::min(K, static_cast<int>(final.size())));
    for (int i = 0; i < std::min(K, static_cast<int>(final.size())); ++i) {
        result.push_back(final[i].first);
    }
    return result;
}
