# Design Proposal – URL Normalizer

The **URL Normalizer** is responsible for converting extracted URLs into a canonical and consistent format before they are processed by the crawler. Since the same webpage can often be represented by multiple URL variations, the URL Normalizer ensures that logically identical URLs are transformed into a single standardized representation. This helps eliminate duplicate crawling, improves storage efficiency, and allows the Seen Store to accurately detect previously visited pages.

---

## Section 1 — Public API

### Method 1

```cpp
std::string normalize(const std::string& url, const std::string& baseUrl = "");
```

**Purpose**

Converts a raw or relative URL into a normalized absolute URL.

**Parameters**

- `url` – The URL extracted from the webpage.
- `baseUrl` – The URL of the current webpage, used to resolve relative links.

**Returns**

- A normalized absolute URL.
- An empty string if the URL is invalid or cannot be normalized.

---

## Section 2 — Internal Representation

The URL Normalizer is a stateless component. It does not permanently store any URLs or maintain any internal data structures. Instead, it processes one URL at a time and returns its normalized representation.

### Temporary Variables

```cpp
std::string scheme;
```

Stores the URL scheme (for example, `http` or `https`).

```cpp
std::string host;
```

Stores the hostname after converting it to lowercase.

```cpp
std::string path;
```

Stores the normalized path after resolving relative directory references.

```cpp
std::string query;
```

Stores the query string, if present.

These variables exist only during the normalization process and are destroyed once the function returns.


## Section 3 — Time Complexity

### normalize(const std::string& url)

**Time Complexity:** **O(n)**

where **n** is the length of the input URL.

Each character of the URL is examined at most a constant number of times while extracting components, converting characters to lowercase, resolving relative paths, and constructing the normalized URL.

**Space Complexity:** **O(n)**

where **n** is the length of the normalized URL, since temporary strings are created while processing the input.

---

## Section 4 — Future Compatibility

The URL Normalizer has been designed as an independent utility component that can be reused throughout the crawler. By separating URL normalization from the crawler's control logic, future enhancements can be introduced without changing the public interface.

Future versions may support additional normalization rules such as removing tracking parameters (for example, `utm_*`), canonicalizing internationalized domain names (IDNs), handling additional URL schemes, and applying configurable normalization policies. Since the component exposes a simple `normalize()` interface, these enhancements can be implemented internally without affecting the Crawler, Frontier, Seen Store, or other components.