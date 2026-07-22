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

### Attempt 1

Initially verified components only through isolated unit tests.

After integrating them into the crawler workflow, additional end-to-end testing was performed to validate the complete execution pipeline.

---

### Attempt 2

Initially assumed that connecting the components would be sufficient for correct execution.

Multiple crawler runs revealed the importance of validating data flow between each stage, ensuring URLs were normalized, checked, fetched, and stored in the correct sequence.

---

### Attempt 3

Initially retained temporary debugging statements during integration.

After successful testing, unnecessary debugging code was removed and the project structure was cleaned to improve readability and maintainability.

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