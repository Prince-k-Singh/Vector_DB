#include <cassert>
#include <iostream>
#include <set>
#include <vector>

#include "flat_search.h"
#include "vector_store.h"

int main() {

    // ---------------------------------------------------------
    // 1. Load SIFT-small datasets
    // ---------------------------------------------------------

    const std::string base_path =
        "../data/siftsmall/siftsmall_base.fvecs";

    const std::string query_path =
        "../data/siftsmall/siftsmall_query.fvecs";

    const std::string groundtruth_path =
        "../data/siftsmall/siftsmall_groundtruth.ivecs";


    auto base = VectorStoreIO::read_vecs<float>(base_path);

    auto queries = VectorStoreIO::read_vecs<float>(query_path);

    auto groundtruth =
        VectorStoreIO::read_vecs<int32_t>(groundtruth_path);


    // ---------------------------------------------------------
    // 2. Validate dataset sizes
    // ---------------------------------------------------------

    assert(base.size() == 10000);
    assert(queries.size() == 100);
    assert(groundtruth.size() == 100);

    std::cout << "Base vectors: " << base.size() << '\n';
    std::cout << "Queries: " << queries.size() << '\n';
    std::cout << "Ground-truth queries: "
              << groundtruth.size() << '\n';


    // ---------------------------------------------------------
    // 3. Validate dimensions
    // ---------------------------------------------------------

    for (const auto& record : base) {
        assert(record.dimension() == 128);
    }

    for (const auto& query : queries) {
        assert(query.dimension() == 128);
    }

    for (const auto& truth : groundtruth) {
        assert(truth.dimension() == 100);
    }


    // ---------------------------------------------------------
    // 4. Run flat_search for every query
    // ---------------------------------------------------------

    const size_t k = 100;

    size_t total_correct = 0;
    size_t total_possible = queries.size() * k;


    for (size_t i = 0; i < queries.size(); ++i) {

        // Run our brute-force search
        std::vector<int> result =
            flat_search(
                queries[i].vector,
                base,
                k
            );


        // We should receive exactly k results
        assert(result.size() == k);


        // Convert returned IDs into a set
        // so that we can compare membership.
        std::set<int> result_ids(
            result.begin(),
            result.end()
        );


        // Compare against the 100 ground-truth IDs
        for (const auto& truth_record : groundtruth[i].vector) {

            if (result_ids.count(truth_record) > 0) {
                ++total_correct;
            }
        }
    }


    // ---------------------------------------------------------
    // 5. Calculate Recall@100
    // ---------------------------------------------------------

    double recall =
        static_cast<double>(total_correct) /
        static_cast<double>(total_possible);


    std::cout << "Correct matches: "
              << total_correct
              << " / "
              << total_possible
              << '\n';

    std::cout << "Recall@100 = "
              << recall
              << '\n';


    // ---------------------------------------------------------
    // 6. Final validation
    // ---------------------------------------------------------

    assert(recall == 1.0);

    std::cout << "====================================\n";
    std::cout << "FINAL VALIDATION PASSED\n";
    std::cout << "Recall@100 = 1.0 (100%)\n";
    std::cout << "====================================\n";


    return 0;
}