#include "TagGraph.hpp"
#include <algorithm>
#include <iostream>

TagGraph::TagGraph(const std::string& nodesFile, const std::string& edgesFile) {
    // парсим nodes
    std::ifstream inN(nodesFile);
    if (!inN) throw std::runtime_error("Cannot open " + nodesFile);
    std::string line;
    while (std::getline(inN, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        int id; std::string name;
        char comma;
        ss >> id >> comma;
        std::getline(ss, name);
        nodes_.emplace(id, Tag(id, name));
    }
    inN.close();

    // парсим edges
    std::ifstream inE(edgesFile);
    if (!inE) throw std::runtime_error("Cannot open " + edgesFile);
    while (std::getline(inE, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        int u, v; double w; char c1, c2;
        ss >> u >> c1 >> v >> c2 >> w;
        // двунаправленный граф
        adj_[u].emplace_back(v, w);
        adj_[v].emplace_back(u, w);
    }
    inE.close();
}

std::vector<TagGraph::Edge> TagGraph::neighbors(int tagId, size_t N) const {
    auto it = adj_.find(tagId);
    if (it == adj_.end()) return {};

    // Отладочный вывод
    size_t adjSize = it->second.size();
    // Безопасное ограничение N
    size_t cap = std::min(N, adjSize);
    auto vec = it->second;
    vec.resize(cap);

    // Убедимся, что кап никак не больше adjSize
    return vec;
}


double TagGraph::similarity(int u, int v) const {
    auto it = adj_.find(u);
    if (it == adj_.end()) return 0.0;
    for (auto &e : it->second) {
        if (e.first == v) return e.second;
    }
    return 0.0;
}
