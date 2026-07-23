# Design Journal

### Date: 21/07/2026

---

## Section 1 — Specific Bugs

### Bug 1

**Issue:** During integration of the crawler components, it was necessary to ensure that URLs already processed by the crawler were not fetched or stored again.

**Observation:** Integration testing confirmed that `SeenStore` correctly filtered duplicate URLs before they reached the fetching and storage stages, preventing redundant processing.

---

### Bug 2

**Issue:** The crawler workflow required proper coordination between `Frontier`, `URLNormalizer`, `Fetcher`, and `PageStorage` so that each component received valid input from the previous stage.

**Observation:** After connecting the components, the crawler successfully followed the expected execution flow, processing URLs in FIFO order and storing fetched pages correctly.

---

### Bug 3

**Issue:** Before finalizing the project, it was necessary to verify that all components worked together without interface mismatches or documentation inconsistencies.

**Observation:** A complete review confirmed that the implemented APIs, memory diagrams, and documentation accurately represented the final codebase.

---

## Section 2 — Failed Attempts

### Attempt 1 — Integrating the Complete Crawler Workflow

Initially, all crawler components had been tested individually, so I expected that simply connecting them together would result in a fully functional crawler. However, after integrating the modules, several logical issues became apparent because the interaction between components was different from their isolated behavior.

During testing, it became clear that the crawler needed to follow a strict sequence of operations. URLs had to be normalized before checking for duplicates, pages should only be marked as visited after a successful download, and downloaded pages had to be stored before extracting additional links. Performing these operations in an incorrect order either caused duplicate processing or prevented failed pages from being retried.

After analyzing the crawler workflow, the execution order was reorganized so that every URL is first normalized, then checked against the `SeenStore`, fetched using the `Fetcher`, stored in the `PageStorage`, and finally processed for outgoing links. This resulted in a consistent and reliable crawling pipeline.

---

### Attempt 2 — Optimizing Page Storage

The initial implementation of the `PageStorage` component searched the storage file sequentially whenever `getPage()` or `hasPage()` was called. Although this implementation worked correctly for a small number of pages, testing revealed that retrieval became increasingly inefficient as the storage file grew because every lookup required scanning the entire file.

To improve performance, the storage mechanism was redesigned to build an in-memory index during initialization. The `buildIndex()` function scans the storage file once when the program starts and stores a mapping between each URL and its corresponding file offset. Additional data structures were introduced to maintain the relationship between page IDs and URLs.

After this redesign:

- `getPage()` directly seeks to the stored file offset instead of scanning the file.
- `hasPage()` performs a hash table lookup instead of reading the storage file.
- `pageCount()` returns the cached value maintained during indexing.
- `getURLByID()` retrieves URLs directly from the stored ID mapping.

This significantly improved retrieval performance while keeping the HTML content stored persistently on disk.

---

### Attempt 3 — Validating Integration Through Repeated Testing

Initially, I assumed that if the crawler completed without crashing, the integration was correct. However, repeated crawler executions revealed several logical issues that were not immediately obvious.

During testing, I observed situations where the storage file contained more pages than expected because previous crawl data remained in the file. Since the Page Storage uses an append-only design, running the crawler multiple times without clearing the storage naturally increased the number of stored records. I also verified that duplicate URLs were correctly filtered by the `SeenStore`, that failed downloads were not incorrectly marked as visited, and that the crawler respected both the maximum depth and maximum page limits.

These repeated integration tests helped distinguish actual implementation bugs from expected behavior, verified that all components interacted correctly, and ensured that the final crawler behaved consistently under multiple execution scenarios.

---

## Section 3 — Design Decisions

Today's work focused on integrating all completed crawler modules into a unified workflow and preparing the project for final submission.

The following design decisions were finalized:

* Integrated `Frontier`, `SeenStore`, `URLNormalizer`, `Fetcher`, and `PageStorage` into the crawler workflow.
* Verified FIFO traversal using the `Frontier`.
* Confirmed duplicate URL filtering through `SeenStore`.
* Ensured every URL passed through `URLNormalizer` before fetching.
* Verified successful HTML retrieval using `Fetcher`.
* Confirmed correct page storage through `PageStorage`.
* Cleaned the project structure and reviewed documentation before submission.

These decisions ensure that the crawler functions as a complete integrated system while maintaining modularity and ease of maintenance.

---

## Section 4 — Code Reference

**Commit Hashes** : `8cba68929388661c4f57a6cb60252d6e1d68d9e0`
**Commit Hashes** : `e14288c231fd8e5096d54911c2b2eaa563b55bae`
**Commit Hashes** : `d069d8a76352cc00f914c68e914a3120644da092`
**Commit Hashes** : `bc967c81fa7eb64bb733cf9205f8c24951d5cb0c`
**Commit Hashes** : `cf24e5e4212a4ae7313c3c57f902391c478138b0`
**Commit Hashes** : `4ab31e3062acd2550b995bf8a587f70fe1c7df4c`

### Files Modified

* `src/crawler.cpp`
* `src/frontier.cpp`
* `src/seenStore.cpp`
* `src/urlNormalizer.cpp`
* `src/fetcher.cpp`
* `src/pageStore.cpp`
* `main.cpp`

### Major Sections Updated

* Crawler Workflow Integration
* End-to-End Integration Testing
* Component Interaction Validation
* Project Cleanup
* Documentation Review
* Final Project Verification

---

## Section 5 — Learning Reflection

Today's work demonstrated the importance of integrating independently tested modules into a complete software system. Although each component functioned correctly in isolation, successful integration required verifying that data flowed correctly through every stage of the crawler.

Testing the complete workflow reinforced how modular software design simplifies development by allowing components such as `Frontier`, `SeenStore`, `URLNormalizer`, `Fetcher`, and `PageStorage` to interact through well-defined interfaces. The final review and cleanup also highlighted the importance of maintaining consistency between implementation and documentation.

Overall, today's work emphasized that thorough integration testing and project refinement are essential steps in delivering reliable and maintainable software.