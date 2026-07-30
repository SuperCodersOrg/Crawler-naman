# Design Journal

### Date: 27/07/2026

---

## Section 1 — Specific Bugs

### Bug 1

**Issue:** During crawler execution, some unit tests failed because duplicate URLs were occasionally processed more than once, leading to unexpected crawler behavior.

**Observation:** The crawler workflow was reviewed to ensure that every URL was checked against the `SeenStore` before processing. This eliminated duplicate page visits and restored the expected crawling sequence.

---

### Bug 2

**Issue:** The HTML parser included unwanted content from certain HTML structures, particularly when comments and nested tags appeared together.

**Observation:** The parsing logic was refined to correctly identify HTML comments and skip all markup while preserving only visible text. This produced cleaner output for indexing.

---

### Bug 3

**Issue:** Several newly implemented features lacked automated verification, making it difficult to detect regressions after modifying the parser.

**Observation:** Google Test cases were written for the HTML parser and crawler components, allowing functionality to be validated automatically after every code change.

---

## Section 2 — Failed Attempts

### Attempt 1 — Duplicate URL Handling

Initially, duplicate URL detection relied solely on checking URLs after they were removed from the `Frontier`. Although functional, this caused unnecessary processing because duplicate URLs still occupied space in the queue.

The crawler logic was revised to consistently validate URLs using the `SeenStore` before processing, ensuring that duplicate pages were skipped and crawler execution remained efficient.

---

### Attempt 2 — HTML Parsing

The first parser implementation removed HTML tags but did not consistently handle comments and irregular whitespace, producing noisy output for some webpages.

The parser was improved to explicitly detect HTML comments, ignore markup completely, and normalize whitespace while extracting visible text, resulting in much cleaner plain text.

---

### Attempt 3 — Manual Verification

Initially, parser correctness was verified by manually comparing extracted text with expected output. While suitable for small examples, this approach became increasingly time-consuming as more edge cases were introduced.

Google Test was adopted to automate validation, allowing parser behavior to be verified consistently across multiple HTML inputs without repeated manual inspection.

---

## Section 3 — Design Decisions

Today's work focused on improving crawler correctness, parser reliability, and automated testing.

The following design decisions were finalized:

* Refined duplicate URL handling using the `SeenStore`.
* Improved HTML parsing by correctly skipping comments and HTML tags.
* Normalized extracted whitespace for cleaner indexing input.
* Added comprehensive Google Test cases for the HTML parser.
* Added automated tests covering crawler behavior and parser edge cases.
* Removed temporary debugging statements after successful validation.
* Verified stable project compilation after implementing the fixes.

These improvements increased the correctness, maintainability, and reliability of the crawler and indexing components.

---

## Section 4 — Code Reference

**Commit Hashes** : `a92e21dddeda34586298bfa066ecdf45d4d01d3a`
**Commit Hashes** : `150662a405d59c185962cbfd55fc282a8402ce25`
**Commit Hashes** : `7ccc61cc2c33581c844db4b8f78defc45b3031ef`
**Commit Hashes** : `3bbbffe018c59ce07125559077e87b0089447e53`
**Commit Hashes** : `5e9fb0945c3ba70f96c6cbca60171915b4c91c59`
**Commit Hashes** : `85fe5af33a7d233e0ba9c66565136e11f4012fdb`
**Commit Hashes** : `9aa22f6b5b67246ca2f907f8a6201237e4cfa41c`
**Commit Hashes** : `dcf3a81710312528fc1c7a908afa0d8d63e92cab`
**Commit Hashes** : `ac5a7f42a1397f1a31cbd76d9c41467c18123d4a`
**Commit Hashes** : `e96ee82451a227d60a70495d24c7e67751ce865b`
**Commit Hashes** : `79234fdb7b093d0a3ab023f3218978f9d3e20080`

### Files Modified

* `src/crawler.cpp`
* `src/htmlParser.cpp`
* `include/htmlParser.h`
* `tests/htmlParser_tests.cpp`
* `tests/crawler_tests.cpp`

### Major Sections Updated

* Duplicate URL Handling
* HTML Parsing Logic
* Comment Skipping
* Whitespace Normalization
* Google Test Cases
* Parser Validation

---

## Section 5 — Learning Reflection

Today's work demonstrated the value of combining debugging with automated testing. While manual testing helped identify the initial issues, Google Test provided a repeatable way to verify functionality after every change. This reduced the effort required to validate fixes and increased confidence in the implementation.

Improving the HTML parser also reinforced the importance of handling edge cases carefully. Small parsing errors can propagate into the indexing stage and reduce the quality of search results. Building reliable preprocessing logic and supporting it with automated tests makes the overall system more robust and easier to maintain as new features are added.
