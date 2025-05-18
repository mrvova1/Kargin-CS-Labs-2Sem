#pragma once
#include "Tag.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

class TagGraph {
public:
    using Edge = std::pair<int,double>;

    // nodesFile: CSV "id,name"
    // edgesFile: CSV "id1,id2,similarity"
    TagGraph(const std::string& nodesFile, const std::string& edgesFile);

    // возвращает до N лучших соседей по weight
    std::vector<Edge> neighbors(int tagId, size_t N) const;

    // сила связи или 0.0
    double similarity(int u, int v) const;

private:
    std::unordered_map<int, Tag> nodes_;
    std::unordered_map<int, std::vector<Edge>> adj_;
};
