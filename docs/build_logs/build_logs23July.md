# Date : 23 July, 2026

## Session 1

**Duration:** 2 Hours

### Goal
Improve the crawler's storage subsystem by introducing indexing for faster page retrieval and optimizing the `PageStorage` implementation.

### Problem Encountered
The original `PageStorage` implementation scanned the storage file sequentially whenever a page needed to be retrieved. As the number of stored pages increased, lookup performance degraded significantly.

### What I Tried
- Reviewed the existing page storage mechanism.
- Designed an in-memory index to map URLs to their corresponding file offsets.
- Implemented index construction while initializing `PageStorage`.
- Added caching for the total number of stored pages.
- Verified that page retrieval used the index instead of scanning the complete file.

### Solution
Implemented an indexing mechanism that builds a URL-to-offset map during initialization. This allows direct access to stored pages while maintaining an accurate cached page count.

### Outcome
Successfully optimized page retrieval, significantly reducing lookup time by eliminating repeated file scans.

### Key Learning
Maintaining an in-memory index greatly improves file-based storage performance while introducing only a small initialization overhead.

---

## Session 2

**Duration:** 2 Hours

### Goal
Implement persistence support for the crawler's `Frontier` so crawling progress can be recovered after interruptions.

### Problem Encountered
The frontier existed only in memory, causing all queued URLs to be lost whenever the crawler terminated unexpectedly. A recovery mechanism was required without affecting the normal crawling workflow.

### What I Tried
- Designed a checkpoint-based persistence mechanism.
- Added automatic loading of the frontier during initialization.
- Implemented periodic checkpoint creation after a fixed number of queue modifications.
- Added support for manually creating checkpoints.
- Added functionality to remove the checkpoint file after a successful crawl.

### Solution
Implemented persistent storage for the `Frontier` by periodically writing the queue contents to disk and restoring them during startup. Updated the crawler to resume crawling from the saved frontier instead of always starting from the seed URL.

### Outcome
The crawler can now recover queued URLs after unexpected interruptions, improving reliability for long-running crawling tasks.

### Key Learning
Periodic checkpointing provides an effective balance between runtime performance and crash recovery.

---

## Session 3

**Duration:** 2 Hours

### Goal
Extend persistence support to `SeenStore` and integrate persistent state management throughout the crawler.

### Problem Encountered
Although the `Frontier` could now recover queued URLs, the crawler still forgot which pages had already been visited after restarting. This could result in revisiting previously crawled pages.

### What I Tried
- Added persistent storage support for `SeenStore`.
- Maintained a dynamic array of visited URLs to simplify serialization.
- Implemented loading and checkpointing for visited URLs.
- Updated the crawler to checkpoint both `Frontier` and `SeenStore`.
- Performed testing of persistence by simulating crawler restarts.

### Solution
Implemented persistence for `SeenStore` using a file-based checkpoint mechanism similar to the `Frontier`. Updated the crawler workflow to restore both queued and visited URLs during startup and remove persistence files after successful completion.

### Outcome
Successfully completed persistent state management for the crawler. The application can now resume interrupted crawls while preserving both the pending frontier and the set of previously visited pages.

### Key Learning
Reliable crash recovery requires persisting every critical component of the crawler's state rather than only the pending work queue.