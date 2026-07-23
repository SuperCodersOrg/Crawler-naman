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

### Attempt 1 — Designing the Page Store

Initially, I considered storing all downloaded webpages entirely in memory using C++ data structures. This approach appeared attractive because retrieving pages would be very fast, and the crawler would not need to perform file I/O during execution.

However, after reviewing the requirements of Project 03, I realized that this design would not be suitable. Once the crawler terminated, all downloaded webpages would be lost, forcing the Indexer to crawl the web again before building the search index. This would unnecessarily increase network traffic and execution time.

To overcome this limitation, the design was changed to use persistent file-based storage. Every downloaded webpage is written to a storage file along with its URL and crawl depth. During program startup, the Page Store scans the storage file once to rebuild its in-memory index (URL to file offset mapping), allowing pages to be retrieved efficiently while keeping the actual HTML content on disk. This approach provides persistence without sacrificing retrieval performance.

---

### Attempt 2 — Integrating libcurl

The Fetcher component depends on the libcurl library for downloading webpages. Initially, I completed the implementation of the Fetcher before configuring the project to locate and link the CURL library correctly.

As a result, the project failed to compile. The compiler reported errors indicating that the required CURL headers and libraries could not be found. Even after installing libcurl, additional linker errors occurred because the library was not properly linked in the CMake configuration.

To resolve these issues, the build configuration was updated by locating the CURL package using CMake's `find_package(CURL REQUIRED)` command and linking the executable with `CURL::libcurl`. Once the dependency was configured correctly, the Fetcher compiled successfully and was able to perform HTTP requests.

---

### Attempt 3 — Windows Build Environment

Initially, development was carried out using the native Windows build environment. During this process, several configuration issues repeatedly interrupted development.

Different CMake generators attempted to use incompatible build tools such as MinGW, NMake, and Visual Studio. Compiler detection frequently failed because the required compiler was either missing from the system PATH or a different compiler installation was being selected than expected. In addition, repository cloning, Git authentication, and file permission issues further complicated the build process.

Some of the errors encountered included:

- CMake failing to detect a valid C or C++ compiler.
- Generator mismatch errors caused by switching between different build systems.
- Linker errors while integrating external libraries.
- Permission denied errors while generating build files inside Windows-managed directories.
- Git authentication and remote repository configuration problems.

After repeatedly troubleshooting these issues, development was migrated to Ubuntu running under Windows Subsystem for Linux (WSL). The Linux environment provided a more consistent compiler toolchain, package management through `apt`, and improved compatibility with CMake and libcurl. Once the environment was migrated, the project built successfully with significantly fewer configuration issues.

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
