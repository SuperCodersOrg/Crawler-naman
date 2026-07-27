# Date : 22 July, 2026

## Session 1

**Duration:** 2 Hours

### Goal
Implement the main crawler workflow by integrating all previously developed components into a single crawling pipeline.

### Problem Encountered
Although all individual modules had been tested successfully, integrating them required careful coordination between the `Frontier`, `Fetcher`, `SeenStore`, `PageStorage`, and `URLNormalizer`. It was necessary to ensure that pages were crawled only once, stored correctly, and that extracted links were processed in the correct order.

### What I Tried
- Implemented the `Crawler` class.
- Integrated `Frontier`, `SeenStore`, `Fetcher`, `PageStorage`, and `URLNormalizer`.
- Added logic to normalize the seed URL before crawling.
- Implemented the crawling loop using the frontier queue.
- Added validation to skip invalid URLs and already visited pages.

### Solution
Successfully integrated all crawler components into a unified workflow. The crawler now fetches pages, stores downloaded HTML, marks visited URLs, and continues crawling newly discovered links while respecting the configured crawl limits.

### Outcome
Completed the implementation of the crawler's core execution flow, enabling automated traversal of static websites.

### Key Learning
A modular architecture greatly simplifies system integration, as independently tested components can be connected with minimal changes.

---

## Session 2

**Duration:** 2 Hours

### Goal
Implement HTML link extraction and integrate it with the crawler to automatically discover new pages.

### Problem Encountered
Extracting valid hyperlinks required handling several HTML edge cases, including missing attributes, quoted values, fragments, unsupported URL schemes, and relative links.

### What I Tried
- Implemented parsing of `<a>` tags.
- Extracted `href` attributes from anchor elements.
- Ignored fragment-only links.
- Filtered unsupported schemes such as `javascript:`, `mailto:`, and `tel:`.
- Normalized extracted URLs using the `URLNormalizer`.
- Added newly discovered URLs to the `Frontier`.

### Solution
Integrated link extraction into the crawling process and validated that normalized links were correctly added to the frontier while avoiding invalid URLs.

### Outcome
The crawler can now automatically discover and enqueue additional pages from downloaded HTML documents.

### Key Learning
Reliable link extraction requires validating HTML structure and filtering unsupported links before adding them to the crawl frontier.

---

## Session 3

**Duration:** 1.5 Hours

### Goal
Verify the complete crawler workflow through end-to-end testing and evaluate its overall behavior.

### Problem Encountered
After integration, it was necessary to ensure that all components interacted correctly and that the crawler respected crawl depth, page limits, and duplicate detection.

### What I Tried
- Executed the crawler on a static website.
- Verified page fetching and storage.
- Confirmed duplicate URL detection using `SeenStore`.
- Checked that extracted links were processed in FIFO order.
- Verified crawl depth limits and maximum page count.
- Added a one-second politeness delay between requests.

### Solution
Performed complete integration testing and validated the interaction between all crawler modules under realistic crawling conditions.

### Outcome
Successfully completed the first fully functional version of the crawler capable of crawling static websites while correctly managing the frontier, visited URLs, page storage, and link extraction.

### Key Learning
End-to-end integration testing is essential for validating interactions between modules that cannot be fully verified through isolated unit tests.