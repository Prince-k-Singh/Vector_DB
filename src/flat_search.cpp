#include <vector>
#include <queue>
#include <utility>
#include <cstddef>

struct VectorRecordFloat {
    int id;
    std::vector<float> vector;
};

/* Squared L2 distance */
float squared_l2(
    const std::vector<float>& a,
    const std::vector<float>& b
) {
    float dist = 0.0f;

    for (size_t i = 0; i < a.size(); i++) {
        float diff = a[i] - b[i];
        dist += diff * diff;
    }

    return dist;
}


/* Brute-force kNN search */
std::vector<int> flat_search(
    const std::vector<float>& query,
    const std::vector<VectorRecordFloat>& base,
    int k
) {
    // Max-heap:
    // pair.first  = distance
    // pair.second = vector ID
    std::priority_queue<
        std::pair<float, int>
    > pq;

    // Check every vector in the dataset
    for (const auto& record : base) {

        // Calculate squared L2 distance
        float dist = squared_l2(query, record.vector);

        // If we don't have k elements yet,
        // simply insert this vector.
        if ((int)pq.size() < k) {
            pq.push({dist, record.id});
        }

        // Otherwise, compare against the worst
        // vector currently present in the heap.
        else if (dist < pq.top().first) {
            pq.pop();
            pq.push({dist, record.id});
        }
    }

    // Extract IDs.
    // Since this is a max-heap, we get
    // farthest -> closest.
    std::vector<int> result;

    while (!pq.empty()) {
        result.push_back(pq.top().second);
        pq.pop();
    }

    // Reverse to get closest -> farthest.
    std::reverse(result.begin(), result.end());

    return result;
}