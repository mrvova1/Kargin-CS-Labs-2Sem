#include "UserProfile.hpp"
#include <cmath>

UserProfile::UserProfile(const std::vector<std::pair<int,int>>& tagCounts,
                         int totalUsers,
                         const std::unordered_map<int,int>& docFreq)
{
    // tf = count, idf = log(N / df)
    for (auto &p : tagCounts) {
        int tagId = p.first, cnt = p.second;
        auto it = docFreq.find(tagId);
        double df = (it!=docFreq.end()? it->second : 1);
        double idf = std::log(static_cast<double>(totalUsers)/df + 1.0);
        tfidf_[tagId] = cnt * idf;
    }
}

double UserProfile::weight(int tagId) const {
    auto it = tfidf_.find(tagId);
    return it!=tfidf_.end() ? it->second : 0.0;
}

void UserProfile::setFeatureWeight(const std::string& f, double w) {
    featureWeights_[f] = w;
}

double UserProfile::featureWeight(const std::string& f) const {
    auto it = featureWeights_.find(f);
    return it!=featureWeights_.end() ? it->second : 0.0;
}
