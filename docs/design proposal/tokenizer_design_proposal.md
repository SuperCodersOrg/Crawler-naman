# Tokenizer

The **Tokenizer** is responsible for splitting plain text into individual words (tokens). It receives the plain text extracted by the HTML Parser and separates it into a sequence of tokens based on whitespace and delimiter characters. The generated tokens are then passed to the Word Normalizer for further processing.

The Tokenizer does not remove punctuation, convert characters to lowercase, normalize words, or build indexes. Its sole responsibility is to identify word boundaries and produce individual tokens.

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
- An empty array if the input text contains no valid tokens.

---

# Section 2 — Internal Representation

The Tokenizer is designed as a lightweight text-processing component that scans the input text sequentially and separates it into individual words. It identifies delimiters such as whitespace and newline characters to determine token boundaries.

Unlike the Word Normalizer, the Tokenizer does not modify the extracted words. It simply identifies where each word begins and ends.

## Private Data Members

### 1. DynamicArray<std::string> tokens

```cpp
DynamicArray<std::string> tokens;
```

The `tokens` array temporarily stores every word extracted from the input text.

Each completed token is appended to this array before the final collection is returned to the caller.

The array is cleared before every tokenization operation.

---

### 2. std::string currentToken

```cpp
std::string currentToken;
```

The `currentToken` buffer stores the characters belonging to the word currently being processed.

Characters are appended until a delimiter is encountered, after which the completed token is inserted into the `tokens` array and the buffer is cleared.

---

## Data Flow

The Tokenizer performs the following sequence of operations internally:

1. Receive plain text from the HTML Parser.
2. Scan the text character by character.
3. Append non-delimiter characters to the current token.
4. When a delimiter is encountered, store the completed token.
5. Continue until the end of the text.
6. Store the final token, if one exists.
7. Return the collection of extracted tokens.

Since the text is processed sequentially, each character is examined only once.

---

# Section 3 — Failure Handling

The Tokenizer is designed to handle invalid or empty input gracefully.

If the input text is empty, the Tokenizer immediately returns an empty collection.

Multiple consecutive delimiters are treated as a single separator and do not generate empty tokens.

Leading and trailing whitespace are ignored automatically.

If the input contains only whitespace characters, the returned collection is empty.

By treating delimiter sequences correctly, the Tokenizer ensures that only meaningful tokens are forwarded to the next processing stage.

---

# Section 4 — Complexity Estimates

## tokenize(const std::string& text)

**Time Complexity:** **O(n)**

where **n** is the number of characters in the input text.

### Explanation

- Every character is scanned exactly once.
- Delimiter detection requires constant time.
- Characters are appended directly to the current token.
- Completed tokens are inserted into the output array.
- Therefore, the running time grows linearly with the size of the input text.

**Space Complexity:** **O(n)**

where **n** is the total number of characters contained in the generated tokens.

The Tokenizer stores only the extracted tokens before returning them to the caller.

---

# Section 5 — Future Compatibility

The Tokenizer has been designed as an independent text-processing component responsible solely for identifying word boundaries. By separating tokenization from normalization and indexing, future enhancements can be implemented without modifying the existing public interface.

Future versions may support:

- Custom delimiter sets
- Unicode-aware tokenization
- Hyphenated word handling
- Apostrophe handling (e.g., "don't")
- Number recognition
- Language-specific tokenization rules

Since the Tokenizer returns a simple collection of words, these improvements can be incorporated without affecting the HTML Parser, Word Normalizer, or Indexer.