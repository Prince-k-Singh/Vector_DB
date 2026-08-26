#include <cassert>
#include <iostream>
#include <string>

#include "metadata.h"
#include "vector_record.h"

int main() {
    VectorRecord<float> record;

    record.id = 42;
    record.vector = {1.0f, 2.0f, 3.0f, 4.0f};

    assert(record.id == 42);
    assert(record.dimension() == 4);

    record.metadata.data["name"] = std::string("test_vector");
    record.metadata.data["category"] = 7;

    assert(std::any_cast<std::string>(
        record.metadata.data["name"]
    ) == "test_vector");

    assert(std::any_cast<int>(
        record.metadata.data["category"]
    ) == 7);

    std::cout << "VectorRecord tests passed!\n";

    return 0;
}