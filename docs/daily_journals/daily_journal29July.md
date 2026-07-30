# Design Journal

### Date: 29/07/2026

---

## Section 1 — Specific Bugs

### Bug 1

**Issue:** During inverted index generation, repeated occurrences of the same word within a document were not being handled consistently, resulting in duplicate entries in the posting list.

**Observation:** The indexing logic was refined to correctly process repeated words and maintain accurate document associations for each indexed term.

---

### Bug 2

**Issue:** Some extracted tokens contained punctuation and irregular whitespace, causing inconsistent entries in the inverted index.

**Observation:** Additional preprocessing was introduced before indexing to normalize tokens, ensuring that only meaningful searchable words were inserted into the index.

---

### Bug 3

**Issue:** The newly implemented indexing functionality lacked sufficient automated test coverage, making it difficult to verify correctness after code modifications.

**Observation:** Google Test cases were developed to validate index generation for multiple documents, repeated words, and edge-case inputs, providing reliable regression testing.

---

## Section 2 — Failed Attempts

### Attempt 1 — Posting List Generation

Initially, every extracted token was inserted directly into the posting list without checking whether the same document had already been recorded for that word. Although functional, this produced duplicate document entries.

The implementation was refined to ensure that each document is associated correctly with indexed terms while avoiding unnecessary duplication in the posting lists.

---

### Attempt 2 — Token Processing

The first indexing implementation accepted extracted text without additional preprocessing. As a result, punctuation and inconsistent whitespace occasionally appeared as part of indexed terms.

A preprocessing step was added to normalize tokens before insertion, producing a cleaner and more consistent inverted index.

---

### Attempt 3 — Manual Verification

The indexing module was initially verified through manual inspection of generated index data. While useful during early development, this approach became increasingly inefficient as additional scenarios were introduced.

Google Test was adopted to automate validation of the indexing logic, enabling rapid verification after every implementation change.

---

## Section 3 — Design Decisions

Today's work focused on improving the correctness and reliability of the indexing module through preprocessing and automated testing.

The following design decisions were finalized:

* Refined posting list generation for indexed terms.
* Added preprocessing to normalize extracted tokens.
* Improved handling of repeated words during indexing.
* Developed comprehensive Google Test cases for the indexing module.
* Added test coverage for multiple documents and edge cases.
* Cleaned the indexing implementation after successful testing.
* Verified stable compilation after all modifications.

These design decisions improve the accuracy of the inverted index while making future development safer through automated testing.

---

## Section 4 — Code Reference

**Commit Hashes** : `fb7ab945d3b3b0c4e93c234c5afa7b0b1b05bbe9`
**Commit Hashes** : `9c5beeee3fe40296a4318a25bbfac005c6ea4fc2`
**Commit Hashes** : `9f2dbe5298669813afb95ff2b278413dbb08e776`
**Commit Hashes** : `e986b616089608e59021915aa6e8d5b869477bb6`
**Commit Hashes** : `8f73713c9f9ab4a80ef562441c4109e5278f8ccd`
**Commit Hashes** : `bda067be1a14cce843e0396a9d69259440dbfea4`
**Commit Hashes** : `85ca5e2e06e96f116dfe7c838b248547f1a28bab`
**Commit Hashes** : `26593b647a60fd350ee86da68dfa99605440eddc`
**Commit Hashes** : `9d7a36803e36a6cdf22172870e7c40f180fff62c`


### Files Modified

* `src/indexer.cpp`
* `include/indexer.h`
* `tests/indexer_tests.cpp`

### Major Sections Updated

* Inverted Index Generation
* Token Normalization
* Posting List Management
* Duplicate Word Handling
* Google Test Cases
* Code Cleanup

---

## Section 5 — Learning Reflection

Today's work reinforced that building an efficient search engine involves much more than simply storing words. Proper token preprocessing and accurate posting list management are essential for producing a reliable inverted index. Small inconsistencies in token handling can significantly affect the quality of search results.

Developing Google Test cases alongside the implementation also highlighted the value of automated testing. Rather than relying on repeated manual verification, unit tests provide a dependable way to validate functionality after every code change, making future enhancements easier and reducing the likelihood of regressions.
