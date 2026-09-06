#include <cassert>
#include <iostream>
#include <string>

#include "vector_store.h"

int main() {
    const std::string file_path =
    "data/siftsmall/siftsmall_base.fvecs";

    auto vectors =
        VectorStoreIO::read_vecs<float>(file_path);

    std::cout << "Loaded vectors: "
              << vectors.size() << '\n';

    assert(vectors.size() == 10000);

    for (const auto& record : vectors) {
        assert(record.dimension() == 128);
    }

    std::cout << "All vectors have dimension 128\n";
    std::cout << "Part 2 loader test passed!\n";

    return 0;
}