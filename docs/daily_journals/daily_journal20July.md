# Design Journal

### Date: 20/07/2026

---

## Section 1 — Specific Bugs

### Bug 1

**Issue:** While testing the `PageStorage` component, it was necessary to verify that storing an already existing page updated the existing record instead of creating duplicate entries.

**Observation:** After implementing update logic, the storage file correctly replaced the previous record while maintaining an accurate page count.

---

### Bug 2

**Issue:** The `URLNormalizer` needed to correctly process several edge cases including protocol-relative URLs, duplicate slashes, uppercase schemes, fragments, and unsupported protocols.

**Observation:** A few logical issues were identified during testing and corrected. The final implementation successfully handled all required URL formats for the crawler.

---

### Bug 3

**Issue:** Individual crawler components had been implemented separately, but they required systematic testing before integration into the complete crawler workflow.

**Observation:** Independent testing confirmed that each module behaved correctly and exposed no remaining functional issues, providing confidence before beginning component integration.

---

## Section 2 — Failed Attempts

### Attempt 1

Initially assumed that updating an existing page in `PageStorage` might unintentionally increase the stored page count.

After executing multiple update scenarios, the implementation was verified to correctly overwrite the existing record while keeping the page count unchanged.

---

### Attempt 2

Initially tested only basic absolute URLs in the `URLNormalizer`.

Additional testing using relative paths, protocol-relative URLs, fragments, duplicate slashes, and unsupported protocols revealed several edge cases that required refinement before the implementation was finalized.

---

### Attempt 3

Initially considered testing only the integrated crawler.

Instead, each component was tested independently using dedicated test programs, making it significantly easier to isolate and debug individual modules.

---

## Section 3 — Design Decisions

Today's work focused on validating the completed crawler components before implementing the crawler workflow.

The following design decisions were finalized:

* Verified `PageStorage` through insertion, retrieval, and update operations.
* Validated `URLNormalizer` against a comprehensive collection of URL formats and edge cases.
* Confirmed FIFO behavior of the `Frontier` component.
* Verified duplicate detection using the `SeenStore`.
* Tested the `Fetcher` by downloading HTML from static webpages.
* Completed independent verification of all implemented crawler components before integration.

These decisions ensure that each component functions correctly in isolation and provides a reliable foundation for implementing the complete crawler.

---

## Section 4 — Code Reference

**Commit Hashes** : `df8a64307f0ba07b226f535deceffe5cdfad1cc1`
**Commit Hashes** : `fb350202f09b22f222efe2e52fc26b829914bb90`
**Commit Hashes** : `903bc484b0558aef774385c7597aaa1cc1ab7544`
**Commit Hashes** : `a641239b87ec348bbcf22f394861e5ccaf51442f`
**Commit Hashes** : `8aa785d3b2fb01756208bd720de512465242b390`
**Commit Hashes** : `6f7d6ac6820380d465ddd96d1af99616515d3d59`
**Commit Hashes** : `d3f409b7131954582c7c0edaafe9599e576d8f90`
**Commit Hashes** : `c9bbb034707e2e1048961ad0e4f1d835a1811009`
**Commit Hashes** : `8711c85864f53ee11032b28ecbca3f8dcd51aec1`
**Commit Hashes** : `f78c25c8e05e043a4933e315ad9d7eb66341684b`


### Files Modified

* `src/pageStore.cpp`
* `src/urlNormalizer.cpp`
* `src/fetcher.cpp`
* `src/frontier.cpp`
* `src/seenStore.cpp`
* `main.cpp`

### Major Sections Updated

* Page Storage Testing
* URL Normalization Validation
* Fetcher Verification
* Frontier Testing
* SeenStore Testing
* Component Integration Preparation

---

## Section 5 — Learning Reflection

Today's work emphasized the importance of validating individual software components before integrating them into a larger system.

Testing `PageStorage` demonstrated how persistent storage must correctly handle both insertion and updates without compromising data integrity. Extensive testing of the `URLNormalizer` highlighted the numerous edge cases involved in processing web URLs and reinforced the importance of handling different URL formats consistently.

Verifying the `Fetcher`, `Frontier`, and `SeenStore` independently provided confidence that each module behaved as intended. Overall, today's work reinforced that systematic testing and validation are essential steps in developing reliable, maintainable software and significantly reduce the complexity of future integration and debugging.