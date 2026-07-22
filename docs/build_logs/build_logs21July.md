# Date : 21 July, 2026

## Session 1

**Duration:** 2 Hours

### Goal
Integrate all previously developed crawler components into the main crawler workflow and verify end-to-end execution.

### Problem Encountered
Although all individual components were functioning correctly, integrating them required ensuring smooth communication between `Frontier`, `SeenStore`, `Fetcher`, `URLNormalizer`, and `PageStorage`. Care was needed to avoid duplicate URL processing and maintain the correct crawling sequence.

### What I Tried
- Connected `Frontier` with the crawler loop.
- Integrated `SeenStore` to filter already visited URLs.
- Connected `Fetcher` to download page content.
- Passed fetched URLs through `URLNormalizer`.
- Stored fetched pages using `PageStorage`.

### Solution
Implemented the complete crawler workflow where URLs are dequeued from the frontier, normalized, checked against the seen store, fetched, and finally stored in the page storage. Verified that each stage passed data correctly to the next component.

### Outcome
Successfully completed the integration of all core crawler components and verified that the crawler pipeline executed correctly for static webpages.

### Key Learning
A modular design significantly simplifies integration because each component can be connected through well-defined interfaces without requiring major implementation changes.

---

## Session 2

**Duration:** 2 Hours

### Goal
Validate the crawler by executing complete crawl cycles and ensure correct interaction between all components.

### Problem Encountered
During integration testing, it was necessary to verify that duplicate URLs were skipped, pages were stored correctly, and the crawling process followed the expected FIFO traversal.

### What I Tried
- Executed the crawler using sample seed URLs.
- Verified that duplicate URLs were ignored.
- Checked the order in which URLs were processed.
- Confirmed successful storage of downloaded pages.
- Observed crawler output for correctness.

### Solution
Performed multiple execution runs with different test inputs and verified that the crawler maintained the correct workflow throughout execution.

The testing confirmed:
- Correct FIFO traversal using `Frontier`.
- Proper duplicate detection using `SeenStore`.
- Successful page retrieval through `Fetcher`.
- Correct URL normalization before processing.
- Accurate page storage without duplicate records.

### Outcome
Confirmed that the crawler performed complete crawl operations correctly and that all integrated components worked together as expected.

### Key Learning
End-to-end testing validates not only individual modules but also the correctness of data flow between interconnected components.

---

## Session 3

**Duration:** 1.5 Hours

### Goal
Review the completed crawler implementation, organize the project structure, and prepare the project for final submission.

### Problem Encountered
Before finalizing the project, it was necessary to ensure that the codebase was organized, documentation reflected the final implementation, and no obsolete test files or debugging code remained.

### What I Tried
- Reviewed the overall project structure.
- Removed temporary debugging statements.
- Verified source and header file organization.
- Checked memory diagrams and design documents against the implementation.
- Performed a final compilation of the complete project.

### Solution
Completed a final project review, cleaned unnecessary code, and confirmed that the documentation accurately represented the implemented crawler architecture.

### Outcome
Prepared the crawler project for submission with all core components integrated, tested, documented, and organized.

### Key Learning
A final review and cleanup phase improves maintainability, ensures consistency between documentation and implementation, and helps deliver a polished software project.