# Tokenizer

The **Tokenizer** is responsible for splitting plain text into individual words (tokens). It receives the plain text extracted by the HTML Parser and separates it into a sequence of tokens by identifying whitespace characters as token delimiters. The generated tokens are then passed to the Word Normalizer for further processing.

The Tokenizer does not remove punctuation, convert characters to lowercase, normalize words, or build indexes. Its sole responsibility is to identify token boundaries and produce individual tokens.

---

# Section 1 — Public API

## Method 1

```cpp
DynamicArray<std::string> tokenize(const std::string& text);
```

### Purpose

Splits the input text into individual tokens by identifying word boundaries.

### Parameters

- `text` — The plain text extracted from a webpage.

### Returns

- A `DynamicArray<std::string>` containing all extracted tokens.
- An empty collection if no valid tokens are found.

---

# Section 2 — Internal Representation

The Tokenizer is designed as a lightweight, stateless text-processing component. It scans the input text sequentially, identifies whitespace characters as token delimiters, and constructs individual tokens one character at a time.

Unlike the Word Normalizer, the Tokenizer does not modify the extracted words. It simply determines where each token begins and ends before returning the resulting collection.

## Private Helper Methods

### 1. addToken()

```cpp
void addToken(DynamicArray<std::string>& tokens,
              std::string& currentToken) const;
```

### Purpose

Adds the current token to the output collection if it is not empty.

This helper method performs three operations:

- Checks whether the current token contains any characters.
- Appends the completed token to the output collection.
- Clears the token buffer so that the next token can be constructed.

Using a helper method avoids duplicating this logic whenever a delimiter is encountered or when the end of the input is reached.

---

## Data Flow

The Tokenizer performs the following sequence of operations internally:

1. Receive plain text from the HTML Parser.
2. Initialize an empty token collection.
3. Scan the input text character by character.
4. Append non-whitespace characters to the current token.
5. When whitespace is encountered, store the completed token.
6. Continue scanning until the end of the text.
7. Store the final token, if one exists.
8. Return the collection of extracted tokens.

Since the input text is processed sequentially, each character is examined only once.

---

# Section 3 — Failure Handling

The Tokenizer is designed to handle empty or whitespace-only input gracefully.

If the input text is empty, the Tokenizer immediately returns an empty collection.

Multiple consecutive whitespace characters are treated as a single delimiter and therefore do not generate empty tokens.

Leading and trailing whitespace are ignored automatically.

If the input consists entirely of whitespace characters, the returned collection is empty.

By treating delimiter sequences correctly, the Tokenizer ensures that only meaningful tokens are forwarded to the Word Normalizer.

---

# Section 4 — Complexity Estimates

## tokenize(const std::string& text)

**Time Complexity:** **O(n)**

where **n** is the number of characters in the input text.

### Explanation

- Every character is examined exactly once.
- Checking whether a character is whitespace requires constant time.
- Characters are appended directly to the current token.
- Completed tokens are appended to the output collection.
- Therefore, the running time grows linearly with the size of the input text.

**Space Complexity:** **O(n)**

where **n** is the total number of characters contained in the generated tokens.

The Tokenizer stores only the extracted tokens before returning them to the caller.

---

# Section 5 — Future Compatibility

The Tokenizer has been designed as an independent text-processing component responsible solely for identifying token boundaries. Because it performs only token extraction, future improvements can be incorporated without affecting the HTML Parser, Word Normalizer, or Indexer.

Future versions may support:

- Configurable delimiter sets
- Unicode-aware tokenization
- Hyphenated word recognition
- Apostrophe handling (e.g., `"don't"`)
- Number recognition
- Language-specific tokenization rules
- Custom tokenization strategies

Since the Tokenizer exposes a simple collection of extracted words, these enhancements can be implemented while preserving the existing public API.