#pragma once

#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "vector_record.h"

class VectorStoreIO {
public:
    template <typename T>
    static std::vector<VectorRecord<T>> read_vecs(
        const std::string& file_path
    ) {
        std::ifstream file(file_path, std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error(
                "Failed to open file: " + file_path
            );
        }

        std::vector<VectorRecord<T>> records;
        int id = 0;

        while (true) {
            int32_t dim;

            // Read dimension
            if (!file.read(
                    reinterpret_cast<char*>(&dim),
                    sizeof(dim)
                )) {
                break; // EOF
            }

            // Create record
            VectorRecord<T> record;
            record.id = id++;

            // Allocate space for vector
            record.vector.resize(dim);

            // Read vector data
            if (!file.read(
                    reinterpret_cast<char*>(record.vector.data()),
                    static_cast<std::streamsize>(dim * sizeof(T))
                )) {
                throw std::runtime_error(
                    "Unexpected end of file while reading vector data"
                );
            }

            records.push_back(std::move(record));
        }

        return records;
    }
};