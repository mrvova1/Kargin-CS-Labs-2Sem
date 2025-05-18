#include "RecommenderEngine.hpp"
#include "ContentModel.hpp"
#include "CollaborativeModel.hpp"
#include "GraphModel.hpp"
#include "RLModel.hpp"
#include "UserProfile.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

// --- CSV-лоадеры ---
std::vector<std::pair<int,int>> loadTagCounts(const std::string& path) {
    std::vector<std::pair<int,int>> out;
    std::ifstream in(path);
    std::string line;
    // пропускаем заголовок
    std::getline(in, line);
    while (std::getline(in, line)) {
        std::istringstream ss(line);
        int tag, cnt;
        char comma;
        ss >> tag >> comma >> cnt;
        out.emplace_back(tag, cnt);
    }
    return out;
}

std::unordered_map<int,int> loadDocFreq(const std::string& path) {
    std::unordered_map<int,int> out;
    std::ifstream in(path);
    std::string line;
    std::getline(in, line);
    while (std::getline(in, line)) {
        std::istringstream ss(line);
        int tag, df;
        char comma;
        ss >> tag >> comma >> df;
        out[tag] = df;
    }
    return out;
}

std::vector<ContentModel::Item> loadItems(const std::string& path) {
    std::vector<ContentModel::Item> out;
    std::ifstream in(path);
    std::string line;
    std::getline(in, line);
    while (std::getline(in, line)) {
        std::istringstream ss(line);
        int itemId;
        std::string tagsField;
        char comma;
        ss >> itemId >> comma >> tagsField;
        // разбить tagsField по ';'
        std::vector<int> tags;
        std::istringstream ts(tagsField);
        std::string tok;
        while (std::getline(ts, tok, ';')) {
            tags.push_back(std::stoi(tok));
        }
        out.emplace_back(itemId, tags);
    }
    return out;
}

std::vector<CollaborativeModel::SimilarUser> loadSimUsers(const std::string& path) {
    std::vector<CollaborativeModel::SimilarUser> out;
    std::ifstream in(path);
    std::string line;
    std::getline(in, line);
    while (std::getline(in, line)) {
        std::istringstream ss(line);
        int userId;
        double sim;
        std::string likedField;
        char comma;
        ss >> userId >> comma >> sim >> comma >> likedField;
        std::vector<int> liked;
        std::istringstream ls(likedField);
        std::string tok;
        while (std::getline(ls, tok, ';')) {
            liked.push_back(std::stoi(tok));
        }
        out.emplace_back(userId, sim, liked);
    }
    return out;
}

// --- main ---
int main() {
    TagGraph tagGraph("tags.csv", "edges.csv");

    // 1) Загружаем профили из CSV
    auto tagCounts = loadTagCounts("tag_counts.csv");
    auto docFreq   = loadDocFreq("doc_freq.csv");

    UserProfile user(tagCounts, /*totalUsers=*/1000, docFreq);
    // Задаём веса дополнительных фич
    user.setFeatureWeight("views",   0.3);
    user.setFeatureWeight("time",    0.2);
    user.setFeatureWeight("ratings", 0.5);

    // 2) Загружаем контент
    // auto items    = loadItems("items.csv");

    // std::vector<ContentModel::Item> items = {
    //     {101, {1,3,4}},      // item 101 помечен rock, pop
    //     {102, {2,3}},      // item 102 — pop, jazz
    //     {103, {1,2}}     // item 103 — rock, jazz, blues
    // };

    std::vector<ContentModel::Item> items = {
        {101, {1}},
        {102, {2}},
        {103, {3}},
        {104, {4}},
        {105, {1,2}},
        {106, {1,3}},
        {107, {1,4}},
        {108, {2,3}},
        {110, {2,4}},
        {111, {3,4}},
        {112, {1,2,3}},
        {113, {1,3,4}},
        {114, {1,3}},
        {115, {1,2,3,4}},
    };

    // 3) Загружаем похожих пользователей
    auto simUsers = loadSimUsers("sim_users.csv");

    // 4) Создаём модели
    ContentModel content;
    CollaborativeModel collab(simUsers);
    GraphModel graph(tagGraph);
    RLModel rl(0.2);               // ε = 0.2

    // 5) Рекомендатель
    RecommenderEngine engine("config.json");
    auto recs = engine.recommend(
        user, content, collab, graph, rl,
        items, /*K=*/16);

    // 6) Вывод
    for (int id : recs)
        std::cout << "Recommend item: " << id << "\n";

    return 0;
}
