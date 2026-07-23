# Page Store

The **Page Store** is a persistent storage component responsible for maintaining all webpages downloaded by the web crawler. Each stored page consists of a unique **Page ID**, the webpage's **URL**, its **HTML content**, and the **crawl depth** at which it was discovered. The Page Store acts as a centralized repository that allows crawled pages to be efficiently stored, retrieved, and managed without requiring the crawler to download them again.

Unlike the Frontier and Seen Store, which exist only in memory during crawling, the Page Store writes every crawled webpage to a storage file. This persistent storage allows other components, such as the **Indexer** in Project 03, to process previously crawled webpages even after the crawler has terminated.

---

# Section 1 — Public API

### Method 1: `storePage(string url, string html, int depth)`

Stores a crawled webpage in the Page Storage. If the URL has not been stored previously, a new **Page ID** is assigned automatically and the page is appended to the storage file. If the URL already exists, the updated page is appended while maintaining the same Page ID.

**Return Type:** `void`

---

### Method 2: `getPage(string url)`

Retrieves the HTML content associated with the given URL.

**Return Type:** `string`

---

### Method 3: `getURLByID(int id)`

Retrieves the URL corresponding to the specified Page ID. This method is primarily intended for the Indexer in Project 03, which processes stored webpages sequentially.

**Return Type:** `string`

---

### Method 4: `hasPage(string url)`

Checks whether the specified URL already exists in the Page Storage.

**Return Type:** `bool`

---

### Method 5: `pageCount()`

Returns the total number of unique webpages currently stored.

**Return Type:** `int`

---

# Section 2 — Internal Representation

![Page Store Memory Diagram](../images/page_store_memory_diagram.png)

The Page Storage stores webpage records persistently inside a text file. Every stored record contains the following information:

- **Page ID** – A unique identifier assigned when the page is first stored.
- **URL** – The webpage's unique address.
- **Depth** – Crawl depth of the webpage.
- **HTML Content** – The downloaded HTML source.

Each record is stored in the following format:

```text
###PAGE###
ID:1
URL:https://example.com
DEPTH:0
HTML
<html>...</html>
###ENDHTML###
```

To provide efficient retrieval, the component maintains two in-memory data structures while the program is running:

- **HashMap<string, streampos> pageIndex**

  Maps each URL to the file offset where the latest copy of that page begins. This allows direct access to a page without scanning the entire storage file.

- **DynamicArray<string> pageURLs**

  Stores URLs in Page ID order. The URL corresponding to Page ID *i* is stored at index *i − 1*. This enables constant-time implementation of `getURLByID()`.

When the Page Storage is constructed, the `buildIndex()` function scans the storage file once to reconstruct both data structures. After initialization:

- `getPage()` uses the hash map to jump directly to the required page.
- `hasPage()` performs a hash table lookup.
- `getURLByID()` accesses the DynamicArray directly.
- `pageCount()` returns the cached page count maintained in memory.

---

# Section 3 — Failure Handling

The following failure cases are considered during the design of the Page Storage component.

### 1. Storage File Cannot Be Opened

If the storage file cannot be opened due to an invalid path or insufficient permissions, the requested operation is aborted. During initialization, an empty storage is assumed.

---

### 2. Empty URL

Since the URL uniquely identifies every webpage, an empty URL is rejected and no page is stored.

---

### 3. Page Not Found

If the requested URL does not exist:

- `getPage()` returns an empty string.
- `hasPage()` returns `false`.

Similarly, if an invalid Page ID is supplied to `getURLByID()`, an empty string is returned.

---

### 4. File Write Failure

If the storage file cannot be written, the page is not stored and the existing storage remains unchanged.

---

# Section 4 — Complexity Estimates

### 1. `storePage(string url, string html, int depth)`

- **Best Case:** **O(1)**
- **Average Case:** **O(1)**
- **Worst Case:** **O(1)**

**Reason:**

The URL lookup is performed using a hash table, and new pages are appended directly to the storage file. No sequential scan is required.

---

### 2. `getPage(string url)`

- **Best Case:** **O(1)**
- **Average Case:** **O(1)**
- **Worst Case:** **O(1)**

**Reason:**

The URL is first located using the hash map, which provides the file offset of the stored page. The file stream directly seeks to that location without scanning previous records.

---

### 3. `getURLByID(int id)`

- **Best Case:** **O(1)**
- **Average Case:** **O(1)**
- **Worst Case:** **O(1)**

**Reason:**

The URL is retrieved directly from the DynamicArray using the Page ID as the index.

---

### 4. `hasPage(string url)`

- **Best Case:** **O(1)**
- **Average Case:** **O(1)**
- **Worst Case:** **O(1)**

**Reason:**

The component performs a hash table lookup to determine whether the URL exists.

---

### 5. `pageCount()`

- **Best Case:** **O(1)**
- **Average Case:** **O(1)**
- **Worst Case:** **O(1)**

**Reason:**

The page count is computed once while building the index during construction and is updated whenever a new unique page is stored.

---

# Section 5 — Future Compatibility

The Page Storage is designed specifically to support the **Indexer** in Project 03.

The Indexer processes stored webpages sequentially using the following workflow:

```cpp
for (int id = 1; id <= storage.pageCount(); id++)
{
    std::string url = storage.getURLByID(id);
    std::string html = storage.getPage(url);

    // Parse HTML and build inverted index
}
```

The `pageCount()` function provides the total number of stored pages, while `getURLByID()` allows the Indexer to iterate over every webpage in Page ID order. Once the URL is obtained, `getPage()` retrieves the corresponding HTML content for parsing and token extraction.

Since all webpage data is stored persistently on disk, the Indexer can operate independently of the crawler without downloading webpages again. This separation of responsibilities improves modularity, promotes code reuse, and allows the crawler and Indexer to evolve independently while communicating through a clean storage interface.