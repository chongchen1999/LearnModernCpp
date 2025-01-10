#include <algorithm>
#include <ranges>
#include <vector>

struct DijkstraInfo {
    int vertexID;
    int distance;  // 比较标准
};

bool cmp(const DijkstraInfo& a, const DijkstraInfo& b) {
    return a.distance < b.distance;
}

template <typename T>
struct cmpFunctor {
    static bool operator()(const T& a, const T& b) {
        return a.distance < b.distance;
    }
};

int main() {
    std::vector<DijkstraInfo> vec = {{1, 10}, {2, 5}, {3, 20}, {4, 15}};

    std::ranges::sort(vec, cmp);  // 按照距离排序

    std::ranges::sort(vec, [](const auto& a, const auto& b) {
        return a.distance < b.distance;  // 按照距离排序
    });

    std::ranges::sort(vec, cmpFunctor<DijkstraInfo>());

    return 0;
}
