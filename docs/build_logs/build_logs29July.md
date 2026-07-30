# Date : 29 July, 2026

## Session 1

**Duration:** 2 Hours

### Goal

Debug and refine the HTML parser to improve the quality of extracted text before indexing.

### Problem Encountered

During testing, the parser produced incorrect output for certain HTML structures. Some tags and comments were not handled consistently, resulting in unwanted text being included in the extracted content.

### What I Tried

* Executed parser test cases with different HTML samples.
* Traced the parsing logic step by step.
* Verified handling of HTML comments and nested tags.
* Checked whitespace normalization after text extraction.
* Compared parser output with the expected plain text.

### Solution

Refined the parsing logic to correctly skip comments and HTML tags while preserving only visible content. Improved whitespace handling to produce cleaner output suitable for indexing.

### Outcome

Successfully resolved parsing issues and generated accurate plain text across all tested HTML documents.

### Key Learning

Carefully handling HTML edge cases during preprocessing significantly improves the quality of data available for indexing.

---

## Session 2

**Duration:** 2 Hours

### Goal

Validate the inverted index generation using the extracted page content.

### Problem Encountered

After implementing the indexing logic, it was necessary to verify that words were correctly indexed and associated with the appropriate documents.

### What I Tried

* Indexed multiple sample HTML pages.
* Verified insertion of extracted words into the inverted index.
* Checked handling of repeated words within documents.
* Compared generated posting lists with expected results.
* Reviewed indexing logic for correctness.

### Solution

Validated that each extracted token was inserted into the correct posting list and properly associated with its corresponding document, ensuring accurate inverted index generation.

### Outcome

Successfully confirmed that the indexing module generated correct inverted index entries for the tested webpages.

### Key Learning

Verifying the correctness of the index during development helps prevent search inaccuracies later in the project.

---

## Session 3

**Duration:** 1.5 Hours

### Goal

Develop Google Test cases for the HTML parser and indexing module.

### Problem Encountered

The newly implemented parser and indexing logic needed automated tests to verify correctness across different HTML structures and input scenarios.

### What I Tried

* Created Google Test cases for HTML text extraction.
* Tested parsing of HTML tags and comments.
* Verified whitespace normalization.
* Wrote test cases for inverted index creation.
* Executed the complete Google Test suite after each change.

### Solution

Implemented comprehensive Google Test cases covering normal inputs, edge cases, and invalid HTML. Fixed minor issues discovered during testing until all test cases passed successfully.

### Outcome

Successfully developed and executed automated tests for the parser and indexing module, improving confidence in the implementation.

### Key Learning

Writing unit tests alongside development makes debugging easier and helps ensure future code changes do not break existing functionality.
