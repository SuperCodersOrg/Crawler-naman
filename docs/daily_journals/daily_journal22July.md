# Design Journal

### Date: 22/07/2026

---

## Section 1 — Specific Bugs

### Bug 1

**Issue:** During integration of the crawler, some extracted links were either invalid or duplicated due to differences in URL representation.

**Observation:** Normalizing every extracted URL before inserting it into the `Frontier` and checking the `SeenStore` before processing ensured that only valid, unique URLs were crawled.

---

### Bug 2

**Issue:** While extracting hyperlinks from HTML pages, several anchor tags contained unsupported URLs such as `javascript:`, `mailto:`, `tel:`, or fragment-only links.

**Observation:** Additional validation was introduced during link extraction to ignore unsupported schemes and fragment-only references, preventing invalid URLs from entering the crawler.

---

### Bug 3

**Issue:** After integrating all crawler modules, it was necessary to verify that the crawler correctly respected the maximum crawl depth and page limit while maintaining FIFO traversal.

**Observation:** End-to-end testing confirmed that the crawler stopped when either limit was reached and processed URLs in the expected order without revisiting previously crawled pages.

---

## Section 2 — Failed Attempts

### Attempt 1 — Crawler Integration

Initially, the crawler modules were connected with minimal validation between them. Although the crawler was able to download pages, several invalid or duplicate URLs entered the crawling queue because extracted links were inserted directly into the `Frontier` without sufficient preprocessing.

This resulted in unnecessary processing and repeated visits to equivalent URLs.

The integration was improved by normalizing every extracted URL, filtering unsupported schemes, and consulting the `SeenStore` before processing a page. These changes produced a much more reliable crawling workflow.

---

### Attempt 2 — HTML Link Extraction

The initial implementation of link extraction focused only on simple anchor tags with straightforward `href` attributes. Testing against real HTML pages revealed several additional cases that required handling, including quoted attributes, fragment-only links, protocol-relative URLs, and relative paths.

After extending the extraction logic and integrating the `URLNormalizer`, the crawler was able to discover valid links more consistently while ignoring unsupported references.

---

### Attempt 3 — End-to-End Testing

The first integration tests focused only on verifying whether pages were downloaded successfully. While this confirmed that the `Fetcher` worked correctly, it did not validate the interaction between all crawler components.

The testing strategy was expanded to verify duplicate detection, page storage, FIFO frontier behavior, crawl depth restrictions, maximum page limits, and automatic link discovery. This provided confidence that the complete crawler workflow operated correctly under realistic conditions.

---

## Section 3 — Design Decisions

Today's work focused on completing the integration of all crawler components into a unified crawling workflow.

The following design decisions were finalized:

- Integrated `Frontier`, `Fetcher`, `SeenStore`, `PageStorage`, and `URLNormalizer` into the `Crawler`.
- Normalized every extracted URL before adding it to the crawl queue.
- Ignored unsupported URL schemes and fragment-only links during extraction.
- Used `SeenStore` to prevent revisiting previously crawled pages.
- Enforced maximum crawl depth and page count limits.
- Added a one-second politeness delay between consecutive requests.
- Completed end-to-end testing of the crawler on static websites.

These decisions improved the reliability and correctness of the crawler while providing a solid foundation for future optimizations.

---

## Section 4 — Code Reference

**Commit Hashes** : `4ab31e3062acd2550b995bf8a587f70fe1c7df4c`
**Commit Hashes** : `d41e179f777f44b6375dcc510392274bc4049bd8`
**Commit Hashes** : `cdbe5c02f4cd26a9b3fa89c692752702728fe178`
**Commit Hashes** : `906ec4be564184108f9c97313a023648e215085e`
**Commit Hashes** : `f8684d87aa48d8ced731dddf1040bad56d0fa6d5`
**Commit Hashes** : `f82b8abf71fb698429c998c1b55db36502df1444`
**Commit Hashes** : `2bb5e586d9aa0d6b16b136655b429603a161a34d`
**Commit Hashes** : `61c699e277c6b535cfe6749018db9021b2fbe94a`

### Files Modified

- `src/crawler.cpp`
- `src/fetcher.cpp`
- `src/frontier.cpp`
- `src/pageStore.cpp`
- `src/seenStore.cpp`
- `src/urlNormalizer.cpp`
- `main.cpp`

### Major Sections Updated

- Crawler Integration
- HTML Link Extraction
- URL Validation
- Crawl Workflow
- Integration Testing
- End-to-End Verification

---

## Section 5 — Learning Reflection

Today's work demonstrated the challenges involved in integrating individually tested modules into a complete software system. Although every component functioned correctly in isolation, successful integration required careful coordination between page fetching, URL normalization, duplicate detection, storage, and frontier management.

Implementing robust link extraction emphasized the importance of validating and normalizing external input before processing it. Comprehensive end-to-end testing also highlighted that integration testing is essential for identifying issues that cannot be detected through unit testing alone.

Overall, today's work reinforced that a well-designed modular architecture simplifies system integration while thorough validation ensures the reliability of the complete application.