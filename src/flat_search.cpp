#include "flat_search.h"

#include <cmath>
#include <queue>
#include <stdexcept>


std::vector<int> flat_search(
    const std::vector<float>& query,
    const std::vector<VectorRecord<float>>& base,
    size_t k
) {
    if (k == 0 || base.empty()) {
        return {};
    }

    if (k > base.size()) {
        k = base.size();
    }

    // Max-heap:
    // pair = (distance, vector_id)
    std::priority_queue<std::pair<float, int>> pq;

    // Scan every vector in the database
    for (const auto& record : base) {

        if (record.vector.size() != query.size()) {
            throw std::runtime_error(
                "Query and database vector dimensions do not match"
            );
        }

        // Calculate squared L2 distance
        float distance = 0.0f;

        for (size_t i = 0; i < query.size(); ++i) {
            float diff = query[i] - record.vector[i];
            distance += diff * diff;
        }

        // Add until we have k elements
        if (pq.size() < k) {
            pq.push({distance, record.id});
        }
        // If this vector is better than the worst
        // vector currently in the heap
        else if (distance < pq.top().first) {
            pq.pop();
            pq.push({distance, record.id});
        }
    }

    // Extract IDs from the max-heap
    std::vector<int> result;
    result.reserve(pq.size());

    while (!pq.empty()) {
        result.push_back(pq.top().second);
        pq.pop();
    }

    // Heap gives farthest -> closest,
    // so reverse to get closest -> farthest.
    std::reverse(result.begin(), result.end());

    return result;
}