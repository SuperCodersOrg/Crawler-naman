# Design Journal

### Date: 18/07/2026

---

## Section 1 — Specific Bugs

### Bug 1

**Issue:** Designing the Page Store component required selecting a storage mechanism that would efficiently preserve downloaded pages while remaining compatible with future indexing.

**Observation:** An in-memory design would lose all data after program termination. A persistent file-based storage approach was therefore chosen to ensure that downloaded pages remain available for subsequent components.

---

### Bug 2

**Issue:** Integrating the Fetcher component using **libcurl** introduced multiple compilation and linking issues during project configuration.

**Observation:** The implementation itself was correct, but the build system required proper CMake configuration and correct linking against the CURL library before the component could compile successfully.

---

### Bug 3

**Issue:** Setting up the crawler project in Ubuntu (WSL) resulted in repository configuration and build environment problems.

**Observation:** Git authentication, remote configuration, CMake generator mismatches, and compiler setup all needed to be configured correctly before development could continue smoothly.

---

## Section 2 — Failed Attempts

### Attempt 1

Initially considered storing downloaded pages entirely in memory for faster access.

After evaluating future project requirements, persistent file storage was selected since it provides better compatibility with the Indexer component.

---

### Attempt 2

Initially attempted to build the project before configuring the required libcurl dependency.

After analyzing the compilation errors, the CMake configuration was updated to correctly locate and link the CURL library.

---

### Attempt 3

Initially attempted to continue development using the Windows build environment.

After repeated configuration and generator issues, the project was migrated to Ubuntu (WSL), providing a more stable and consistent development environment.

---

## Section 3 — Design Decisions

Today's work focused on completing the remaining crawler architecture and establishing the development environment.

The following design decisions were finalized:

* Implemented Page Store as a persistent file-based storage component.
* Designed the URL Normalizer to generate canonical URLs before crawling.
* Defined clear responsibilities for the Crawler component and its interaction with supporting modules.
* Implemented the Fetcher using libcurl for downloading webpage contents.
* Added failure handling for unsuccessful HTTP requests.
* Configured the project using CMake for Linux-based development.
* Established Ubuntu (WSL) as the primary development environment.

These decisions improve modularity, maintainability, and future compatibility of the crawler.

---

## Section 4 — Code Reference

### Files Modified

* `DOCS/design proposal/page_store_design_proposal.md`
* `DOCS/design proposal/url_normalizer_design_proposal.md`
* `DOCS/design proposal/crawler_design_proposal.md`
* `include/fetcher.h`
* `src/fetcher.cpp`
* `CMakeLists.txt`

### Major Sections Updated

* Page Store Public API
* URL Normalizer Design
* Crawler Responsibilities
* Failure Handling
* Future Compatibility
* Fetcher Implementation
* Build Configuration

---

## Section 5 — Learning Reflection

Today's work strengthened my understanding of designing software components that interact through clearly defined interfaces while remaining modular and maintainable.

Implementing the Fetcher provided practical experience with integrating third-party libraries into a C++ project and highlighted the importance of build system configuration in addition to implementation. Designing the Page Store and URL Normalizer reinforced the value of planning for future compatibility rather than focusing solely on current functionality.

Configuring the project in Ubuntu also improved my understanding of Linux-based development workflows, Git configuration, CMake, and dependency management. Overall, today's work demonstrated that successful software development depends equally on good architecture, proper tooling, and maintainable implementation.
