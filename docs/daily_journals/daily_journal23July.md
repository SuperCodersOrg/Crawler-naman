# Design Journal

### Date: 23/07/2026

---

## Section 1 — Specific Bugs

### Bug 1

**Issue:** The original `PageStorage` implementation performed a sequential scan of the storage file whenever a page was requested. As the number of stored pages increased, lookup operations became increasingly inefficient.

**Observation:** An in-memory index mapping URLs to file offsets was introduced during initialization. This eliminated repeated file scans and significantly improved page retrieval performance while maintaining accurate page counts.

---

### Bug 2

**Issue:** The crawler initially stored both the `Frontier` and `SeenStore` only in memory. If the application terminated unexpectedly, all pending URLs and visited page information were lost, forcing the crawl to restart from the beginning.

**Observation:** A checkpoint-based persistence mechanism was implemented for the `Frontier`, allowing queued URLs to be written to disk periodically and restored automatically when the crawler restarted.

---

### Bug 3

**Issue:** After implementing persistence for the `Frontier`, the crawler still revisited previously crawled pages because the `SeenStore` was not preserved across executions.

**Observation:** Persistence was extended to the `SeenStore` using a checkpoint file and a serialized list of visited URLs. The crawler now restores both pending and visited URLs, allowing interrupted crawls to resume correctly.

---

## Section 2 — Failed Attempts

### Attempt 1 — Optimizing Page Retrieval

Initially, page retrieval relied on scanning the storage file line by line until the requested URL was found. Although this approach worked correctly for a small number of pages, the lookup time increased proportionally with the size of the storage file.

To improve efficiency, an indexing mechanism was introduced during initialization. Every stored URL is associated with its corresponding file offset, allowing direct access to page data without repeatedly scanning the entire file. This approach significantly improves retrieval performance while requiring only a one-time indexing cost during startup.

---

### Attempt 2 — Frontier Persistence

The first idea for implementing persistence was to save the `Frontier` only when the crawler terminated normally by writing the queue contents in the destructor. Although simple, this approach would fail if the application crashed unexpectedly because destructors are not guaranteed to execute.

The design was replaced with a checkpoint-based mechanism that periodically writes the queue contents to disk after a configurable number of modifications. During startup, the checkpoint file is loaded automatically, allowing the crawler to continue from its previous state.

---

### Attempt 3 — Persisting SeenStore

Initially, persistence for the `SeenStore` was considered by serializing the internal `HashMap` directly. However, the current hash map implementation did not provide an iterator over stored keys, making serialization difficult without modifying the generic data structure.

Instead, a `DynamicArray` of visited URLs was maintained alongside the hash map. The array is serialized during checkpoint creation and reconstructed during startup, while the hash map continues to provide efficient duplicate detection. This approach preserved the existing `HashMap` implementation and simplified persistence.

---

## Section 3 — Design Decisions

Today's work focused on improving the crawler's reliability and storage efficiency through indexing and persistent state management.

The following design decisions were finalized:

- Implemented an in-memory index for `PageStorage` to provide direct page retrieval using file offsets.
- Added cached page counting to avoid repeatedly scanning the storage file.
- Implemented checkpoint-based persistence for the `Frontier`.
- Extended persistence support to the `SeenStore`.
- Integrated checkpoint loading during crawler initialization.
- Updated the crawler to resume interrupted crawls using persisted state.
- Added checkpoint cleanup after successful crawl completion.
- Performed integration testing to verify persistence and crash recovery.

These design decisions improve both the efficiency and fault tolerance of the crawler while maintaining compatibility with the existing architecture.

---

## Section 4 — Code Reference

**Commit Hashes** : `c86c63ee8fe999df3b7ef989845378d28f6963c5`
**Commit Hashes** : `a92e21dddeda34586298bfa066ecdf45d4d01d3a`
**Commit Hashes** : `150662a405d59c185962cbfd55fc282a8402ce25`
**Commit Hashes** : `7ccc61cc2c33581c844db4b8f78defc45b3031ef`

### Files Modified

- `src/pageStore.cpp`
- `src/pageStore.h`
- `src/frontier.cpp`
- `src/frontier.h`
- `src/seenStore.cpp`
- `src/seenStore.h`
- `src/crawler.cpp`

### Major Sections Updated

- Page Storage Indexing
- Cached Page Count
- Frontier Persistence
- SeenStore Persistence
- Checkpoint Recovery
- Crawler Resume Logic
- Persistence Testing

---

## Section 5 — Learning Reflection

Today's work highlighted the importance of designing software for both performance and reliability. Optimizing `PageStorage` with an in-memory index demonstrated how appropriate data structures can dramatically reduce file access time without increasing runtime complexity during normal operation.

Implementing persistence for both the `Frontier` and `SeenStore` reinforced that reliable applications must be able to recover gracefully from unexpected interruptions. The checkpoint-based design proved more robust than relying on normal program termination and allows the crawler to resume long-running tasks without repeating completed work.

Overall, today's development emphasized that efficient storage management, thoughtful recovery mechanisms, and careful integration are essential for building scalable and dependable crawler systems.