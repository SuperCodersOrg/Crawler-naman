# Date : 28 July, 2026

## Session 1

**Duration:** 2 Hours

### Goal

Begin implementation of the Indexer module by developing functionality to extract visible text from HTML pages.

### Problem Encountered

Raw HTML documents contain tags, comments, scripts, and formatting elements that should not be indexed. The challenge was to extract only meaningful visible text while preserving readability.

### What I Tried

* Designed the overall text extraction workflow.
* Parsed HTML character by character.
* Detected the start and end of HTML tags.
* Ignored HTML comments during parsing.
* Collected only visible text outside HTML tags.

### Solution

Implemented the initial version of the HTML parser that scans the document sequentially, skips HTML tags and comments, and appends only visible characters to the output buffer. The parser also normalized whitespace to generate clean text suitable for indexing.

### Outcome

Successfully completed the first version of the HTML text extraction module, producing readable plain text from HTML documents.

### Key Learning

A sequential parsing approach is efficient for static webpages and provides a strong foundation for building the indexing pipeline.

---

## Session 2

**Duration:** 2 Hours

### Goal

Improve the robustness of the HTML parser by handling additional HTML edge cases.

### Problem Encountered

Certain HTML structures, including nested elements and irregular spacing, produced inconsistent output during text extraction. Extra whitespace also reduced the quality of the extracted content.

### What I Tried

* Tested the parser with multiple HTML samples.
* Verified extraction from nested HTML elements.
* Improved whitespace handling.
* Checked behavior with malformed or incomplete tags.
* Compared extracted text against expected output.

### Solution

Enhanced the parser to normalize consecutive whitespace, correctly process nested tags, and produce cleaner textual output. Additional validation ensured that unnecessary characters were removed while preserving readable content.

### Outcome

The parser generated significantly cleaner and more consistent text across different HTML documents, making it suitable for use by the indexing module.

### Key Learning

Handling edge cases early greatly improves parser reliability and reduces issues in later stages of the indexing process.

---

## Session 3

**Duration:** 1.5 Hours

### Goal

Validate the HTML parser through testing and prepare it for integration with the Indexer.

### Problem Encountered

Before integrating the parser into the indexing pipeline, it was necessary to verify that it consistently extracted meaningful text from various webpages.

### What I Tried

* Executed parser tests using different HTML inputs.
* Verified removal of HTML tags and comments.
* Compared extracted output with expected plain text.
* Reviewed the implementation for correctness and readability.
* Cleaned temporary debugging code.

### Solution

Performed comprehensive validation of the parser and confirmed that the extracted output was accurate, readable, and appropriate for indexing. Final code cleanup improved maintainability before integration.

### Outcome

Completed the HTML parsing component and prepared it for integration with the Indexer module in the next development phase.

### Key Learning

Thorough validation of preprocessing components ensures that later stages, such as tokenization and inverted index construction, operate on high-quality input data.
