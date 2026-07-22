# Date : 18 July, 2026

## Session 1

**Duration:** 3 Hours

### Goal

Complete the design proposals for the **Page Store**, **URL Normalizer**, and **Crawler** components by defining their public APIs, internal working, responsibilities, failure handling, and future compatibility.

### Problem Encountered

Designing the architecture of multiple interacting components while ensuring that each component has a well-defined responsibility and integrates seamlessly with the overall crawler pipeline. It was also necessary to maintain compatibility with the future Indexer component.

### What I Tried

* Studied the project requirements for each component.
* Designed the public APIs and internal workflows.
* Identified the interaction between Frontier, SeenStore, URL Normalizer, Fetcher, and Page Store.
* Planned persistent storage for downloaded pages and URL normalization before crawling.

### Solution

Prepared complete design proposals for all three components.

The final documentation includes:

* Public APIs and responsibilities of each component.
* Internal workflow of the crawler.
* Failure handling mechanisms.
* Time complexity analysis.
* Future compatibility with the Project 03 Indexer.
* Component interaction diagrams and architecture.

### Outcome

Successfully completed the design documentation for the remaining crawler components.

### Key Learning

Designing modular components with clearly defined responsibilities simplifies implementation and improves maintainability.

---

## Session 2

**Duration:** 3 Hours

### Goal

Implement the **Fetcher** component and integrate it with the crawler project.

### Problem Encountered

Integrating **libcurl** into the C++ project while handling compiler, linker, and CMake configuration issues across different development environments.

### What I Tried

* Studied the libcurl API.
* Implemented the HTML download callback.
* Configured CMake to locate and link the CURL library.
* Debugged build and linking errors.
* Tested the Fetcher with static websites.

### Solution

Successfully implemented the Fetcher component.

The implementation includes:

* Downloading webpages using libcurl.
* Callback-based HTML storage.
* User-Agent configuration.
* Error handling for failed requests.
* Integration with the crawler workflow.

### Outcome

Completed the Fetcher implementation and verified its integration with the crawler architecture.

### Key Learning

Successfully integrating external libraries requires both proper implementation and correct build-system configuration.

---

## Session 3

**Duration:** 2.5 Hours

### Goal

Set up a stable Linux development environment and prepare the crawler project for development in Ubuntu (WSL).

### Problem Encountered

Faced multiple environment-related issues including Git repository setup, SSH authentication, remote configuration, CMake generator mismatches, and compiler configuration.

### What I Tried

* Configured Git inside Ubuntu.
* Connected the local repository with the GitHub remote.
* Resolved authentication issues.
* Configured the CMake build environment.
* Verified repository status and development workflow.

### Solution

Successfully established the Ubuntu development environment.

The completed setup includes:

* Git configuration and remote repository setup.
* Repository cloning and synchronization with GitHub.
* Linux-based CMake configuration.
* Ready-to-use development workflow for the crawler project.

### Outcome

Completed the migration of the development workflow to Ubuntu, enabling efficient compilation, testing, and version control.

### Key Learning

A properly configured Linux development environment significantly simplifies C++ development, dependency management, and collaboration using Git.
