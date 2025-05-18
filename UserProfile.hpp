#pragma once
#include "Tag.hpp"
#include <unordered_map>
#include <vector>
#include <string>

class UserProfile {
public:
    // tagCounts: vector of (tagId, count)
    // totalUsers, docFreq: для расчёта IDF
    UserProfile(const std::vector<std::pair<int,int>>& tagCounts,
                int totalUsers,
                const std::unordered_map<int,int>& docFreq);

    // tf-idf вес тега
    double weight(int tagId) const;

    // установить вес для дополнительного признака ("views", "time", ...)
    void setFeatureWeight(const std::string& feature, double w);

    // получить вес признака
    double featureWeight(const std::string& feature) const;

private:
    std::unordered_map<int,double> tfidf_;
    std::unordered_map<std::string,double> featureWeights_;
};
