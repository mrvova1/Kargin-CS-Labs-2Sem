#include "RecommenderEngine.hpp"
#include "ContentModel.hpp"
#include "CollaborativeModel.hpp"
#include "GraphModel.hpp"
#include "RLModel.hpp"
#include "UserProfile.hpp"
#include <iostream>

int main() {
    // 1) Граф тегов из файлов
    TagGraph tagGraph("tags.csv", "edges.csv");

    // 2) Профиль пользователя: tagId → count
    //    (например, собрали из логов: сколько раз пользователь встречал каждый тег)
    std::vector<std::pair<int,int>> tagCounts = {
        {1, 10},   // rock — 10 раз
        {3,  2}    // jazz — 2 раза
    };
    // Документ-фреквенси (DF): в скольких пользователях встретился каждый тег
    std::unordered_map<int,int> docFreq = {
        {1, 100},  // 100 пользователей слушали rock
        {2, 150},  // pop — 150
        {3,  50},  // jazz — 50
        {4,  20}   // blues — 20
    };
    // Создаём профиль: C++ сам посчитает TF–IDF
    UserProfile user(tagCounts, /*totalUsers=*/1000, docFreq);
    user.setFeatureWeight("views",   0.3);
    user.setFeatureWeight("time",    0.2);
    user.setFeatureWeight("ratings", 0.5);

    // 3) Метаданные контента: itemId → список tagId
    // std::vector<ContentModel::Item> items = {
    //     {101, {1,2}},      // item 101 помечен rock, pop
    //     {102, {2,3}},      // item 102 — pop, jazz
    //     {103, {1,3,4}}     // item 103 — rock, jazz, blues
    // };
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

    // 4) Похожие пользователи: (userId, similarity, [likedItemId...])
    std::vector<CollaborativeModel::SimilarUser> simUsers = {
        {201, 0.9, {101,103}},  // пользователь 201 похож на 0.9, любит 101 и 103
        {202, 0.6, {102}}       // пользователь 202 похож на 0.6, любит 102
    };

    // 5) Создаём модели
    ContentModel    content;
    CollaborativeModel collab(simUsers);
    GraphModel      graph(tagGraph);
    RLModel         rl(0.2);               // ε = 0.2

    // 6) Основной движок
    RecommenderEngine engine("config.json");
    auto recs = engine.recommend(
        user, content, collab, graph, rl,
        items, /*K=*/50);

    // Выводим результат
    for (int id : recs)
        std::cout << "Recommend item: " << id << "\n";
    return 0;
}
