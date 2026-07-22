# Seen Store
The **SeenStore** is a component of the web crawler that maintains a record of all URLs that have already been discovered during the crawling process. Its primary purpose is to ensure that each URL is processed only once, preventing duplicate crawling, unnecessary network requests, and infinite loops caused by cyclic hyperlinks.

The `SeenStore` provides efficient lookup and insertion operations, allowing the crawler to quickly determine whether a newly discovered URL has already been encountered. Before adding a URL to the **Frontier**, the crawler first checks the `SeenStore`.

- If the URL is **not present**, it is inserted into the `SeenStore` and then added to the **Frontier** for future crawling.
- If the URL **already exists**, it is ignored because it has either been visited previously or has already been scheduled for crawling.

In this project, the `SeenStore` is implemented using the custom **HashMap** developed in Project 01. The hash map stores each URL as a key and provides **O(1)** average-case lookup and insertion, making it well-suited for tracking a large number of unique URLs during web crawling.

## Section 1 : Public API

### `bool contains(string url)`

Returns `true` if the specified URL is already present in the SeenStore. Otherwise, returns `false`.

---

### `void insert(string url)`

Inserts the specified URL into the SeenStore if it is not already present.

---

### `int count()`

Returns the total number of unique URLs currently stored in the SeenStore.

## Section 2 — Internal Representation
![Seen Store Memory Diagram](../images/seen_store_memory_diagram.png)

The `SeenStore` class is implemented using the custom `HashMap<std::string, bool>` developed in Project 01. The hash map stores each URL as the key and a boolean value indicating that the URL has already been visited.

The class maintains a single private data member:

- **seenURLs** – A `HashMap<std::string, bool>` containing all previously discovered URLs.

Each entry in the hash map consists of:

- A `std::string` representing the URL.
- A boolean value indicating that the URL has been recorded.

The underlying hash map uses separate chaining with linked lists to resolve collisions. This allows efficient insertion and lookup of URLs while maintaining average-case **O(1)** performance.

All memory allocation, collision handling, resizing, and rehashing are managed by the custom HashMap implementation from Project 01. The `SeenStore` class simply provides an interface for recording and querying visited URLs.

## Section 3 — Failure Handling

The `SeenStore` class is responsible for maintaining the collection of previously visited URLs. Memory management and hash table operations are handled by the custom HashMap implementation from Project 01.

The following failure cases are handled:

- **Duplicate URLs:** If an attempt is made to insert a URL that already exists in the SeenStore, the insertion is ignored. This ensures that each URL is stored only once.

- **Empty URL:** If an empty string is provided, the URL is rejected and is not inserted into the SeenStore.

These checks ensure that the SeenStore maintains a valid collection of unique URLs throughout the crawling process.

## Section 4 : Complexity Estimates

### 1. `insert(string url)`

- **Best Case:** The insert operation takes **O(1)** time when the target bucket is empty and no collision occurs.<br>

- **Average Case:** The insert operation takes **O(1)** time because the hash function distributes URLs uniformly across the buckets.<br>

- **Worst Case:** The insert operation takes **O(n)** time when all URLs hash to the same bucket, requiring traversal of the entire chain.<br>

---

### 2. `contains(string url)`

- **Best Case:** **O(1)**  
  The URL is found immediately in its corresponding bucket.

- **Average Case:** **O(1)**  
  A well-distributed hash function allows the URL to be located in constant time.

- **Worst Case:** **O(n)**  
  If all URLs collide into a single bucket, the linked list must be traversed completely.

**Reason:**  
The SeenStore is implemented using a hash table with separate chaining. Under normal conditions, lookup is performed in constant time.

---

### 3. `count()`

- **Best Case:** **O(1)**

- **Average Case:** **O(1)**

- **Worst Case:** **O(1)**

**Reason:**  
The HashMap maintains the current number of stored entries internally, allowing the count to be returned directly without traversing the table.

# Section 5 — Future Compatibility

The `SeenStore` class is designed as an independent component for tracking unique URLs during web crawling. It provides a simple interface for checking whether a URL has already been discovered and for recording newly discovered URLs.

Since the implementation is based on the reusable `HashMap` developed in Project 01, the underlying storage mechanism can be improved or replaced without affecting the public interface of the `SeenStore`. Future projects can therefore reuse this component with minimal or no modifications.

Additionally, if future crawler implementations require storing extra information about each URL (such as visit status, timestamp, or crawl priority), the value type of the underlying `HashMap` can be extended while preserving the existing public API.