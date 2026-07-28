# HTML Parser

The **HTML Parser** is responsible for extracting the visible textual content from an HTML document. It removes HTML tags, ignores non-visible elements such as scripts and styles, and returns plain text that can be further processed by the Indexer.

The Parser does not download webpages, tokenize text, normalize words, or build indexes. Its sole responsibility is to transform raw HTML into readable text.

---

# Section 1 — Public API

## Method 1

```cpp
std::string extractText(const std::string& html);
```

### Purpose

Extracts the visible text from an HTML document by removing HTML tags and non-visible content.

### Parameters

- `html` — The raw HTML content of a webpage.

### Returns

- A `std::string` containing the extracted plain text.
- An empty string if no visible text exists.

---

# Section 2 — Internal Representation

![Working of HTML Parser](../images/html_parser_working_diagram.png)

The HTML Parser is designed as a lightweight text-processing component. It scans the HTML document character by character, identifies HTML tags, ignores non-visible sections, and copies only visible text into the output buffer.

Unlike a web browser, the Parser does not attempt to interpret CSS, execute JavaScript, or build a Document Object Model (DOM). It simply extracts readable text.

## Private Data Members

### 1. std::string outputBuffer

```cpp
std::string outputBuffer;
```

The `outputBuffer` temporarily stores the visible text extracted from the HTML document.

Characters outside HTML tags are appended to this buffer until the entire document has been processed.

The buffer is cleared before every parsing operation.

---

### 2. bool insideTag

```cpp
bool insideTag;
```

The `insideTag` flag indicates whether the parser is currently processing an HTML tag.

- `true` indicates characters between `<` and `>`.
- `false` indicates visible webpage content.

Only characters encountered while `insideTag` is `false` are copied into the output buffer.

---

### 3. bool ignoreContent

```cpp
bool ignoreContent;
```

The `ignoreContent` flag is used to skip sections that should not contribute to searchable text.

Examples include:

- `<script> ... </script>`
- `<style> ... </style>`

Characters inside these sections are ignored until the corresponding closing tag is encountered.

---

## Data Flow

The Parser performs the following sequence of operations internally:

1. Receive the raw HTML document.
2. Scan the document from beginning to end.
3. Detect opening and closing HTML tags.
4. Skip all HTML tags.
5. Ignore text inside script and style sections.
6. Copy visible characters into the output buffer.
7. Return the extracted plain text.

The parser processes the document sequentially and requires only a single pass over the HTML.

---

# Section 3 — Failure Handling

The Parser is designed to tolerate malformed HTML whenever possible.

If the input HTML string is empty, the Parser immediately returns an empty string.

If malformed or incomplete HTML tags are encountered, the parser continues scanning the remaining document instead of terminating.

If no visible text is found after processing the document, an empty string is returned.

By treating parsing errors as recoverable, the Parser ensures that malformed webpages do not interrupt the indexing process.

---

# Section 4 — Complexity Estimates

## extractText(const std::string& html)

**Time Complexity:** **O(n)**

where **n** is the number of characters in the HTML document.

### Explanation

- Each character is examined exactly once.
- Detecting HTML tags requires constant-time operations.
- Visible characters are appended directly to the output buffer.
- Therefore, the running time grows linearly with the size of the HTML document.

**Space Complexity:** **O(n)**

where **n** is the size of the extracted plain text.

The parser stores only the resulting text while processing the document.

---

# Section 5 — Future Compatibility

The HTML Parser has been designed as an independent preprocessing component that converts HTML into plain text. Because it performs only text extraction, future improvements can be added without affecting the Indexer or other crawler components.

Future versions may support:

- HTML entity decoding (`&amp;`, `&lt;`, `&gt;`, etc.)
- Extraction of page titles and metadata
- Ignoring additional non-visible HTML elements
- Unicode character handling
- Preservation of paragraph and sentence boundaries

Since the Parser provides a simple plain-text interface, these enhancements can be implemented while preserving the existing public API.