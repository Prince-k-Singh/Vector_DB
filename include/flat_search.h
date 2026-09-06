#pragma once

#include <utility>
#include <vector>

#include "vector_record.h"

std::vector<int> flat_search(
    const std::vector<float>& query,
    const std::vector<VectorRecord<float>>& base,
    size_t k
);