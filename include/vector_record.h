#pragma once

#include <vector>
#include <cstddef>

#include "metadata.h"

template <typename T>
struct VectorRecord {
    int id;
    std::vector<T> vector;
    Metadata metadata;

    size_t dimension() const {
        return vector.size();
    }
};