# Crawler 
The **Crawler** is the main controller of the web crawler. It manages the crawling process by retrieving URLs from the Frontier, ensuring that pages are not revisited using the SeenStore, downloading webpage content, storing the downloaded pages, and discovering new URLs until the specified crawling limits are reached.

## Section 1 — Public API

## Constructor

### **Crawler(int maxDepth, int maxPages)**

Creates a crawler object and initializes the crawler with the maximum crawl depth and the maximum number of pages to download.

### Parameters

- `maxDepth` : Maximum depth up to which hyperlinks will be followed.
- `maxPages` : Maximum number of webpages that may be crawled.


---

## Method 1

### **void crawl(std::string seedURL)**

Starts the crawling process from the given seed URL. The crawler repeatedly removes URLs from the Frontier, downloads webpages, stores them, extracts hyperlinks, and schedules newly discovered URLs until either the maximum page limit, maximum depth is reached, or the Frontier becomes empty.

### Parameters

- `seedURL` : The initial URL from which crawling begins.

### Returns

**void**


## Section 2 : Internal Representation 
![Memory Diagram of Crawler](../images/crawler_memory_diagram.png)

The **Crawler** acts as the central coordinator of the web crawling system. It owns the major components required during crawling and controls how they interact throughout the execution of the program. Rather than implementing individual functionalities such as URL storage or page persistence itself, the crawler delegates these responsibilities to specialized components.

Internally, the crawler maintains:

- A **Frontier** object that stores the URLs waiting to be crawled.
- A **SeenStore** object that keeps track of URLs that have already been visited, preventing duplicate crawling.
- A **PageStorage** object responsible for permanently storing downloaded webpages.
- An integer **maxDepth** that specifies the maximum depth up to which hyperlinks should be followed.
- An integer **maxPages** that limits the total number of webpages that can be crawled during execution.

During execution, the crawler repeatedly removes a URL from the Frontier, checks whether it has already been visited using the SeenStore, downloads the webpage if it is eligible for crawling, stores the downloaded page using the PageStorage component, extracts hyperlinks from the page, and inserts newly discovered URLs back into the Frontier if they satisfy the crawling constraints.

## Section 3 : Failure Handling 

The Crawler is designed to continue its execution even when individual webpages cannot be processed successfully. Instead of terminating the crawling process, it skips the failed URL and proceeds with the remaining URLs in the Frontier.

The crawler handles the following situations:

- **Empty Frontier:** If no URLs remain to be crawled, the crawling process terminates normally.

- **Already Visited URL:** If a URL is already present in the SeenStore, it is ignored to prevent duplicate crawling.

- **Page Download Failure:** If a webpage cannot be downloaded due to network errors, invalid URLs, or server-side issues, the page is skipped and crawling continues.

- **Maximum Depth Reached:** URLs whose depth exceeds the specified maximum depth are not added to the Frontier.

- **Maximum Page Limit Reached:** Crawling stops once the specified maximum number of pages has been processed.

- **Invalid or Empty URL:** Invalid or empty URLs are ignored and are not processed further.

By handling these conditions gracefully, the crawler ensures that failures affecting individual webpages do not interrupt the overall crawling process.

## Section 4 : Complexity Estimates 

### 1. `void crawl(std::string seedURL)`

**Time Complexity:** **O(P × (F + E))**

where:

- **P** = Number of webpages successfully crawled.
- **F** = Time required to fetch and store a webpage.
- **E** = Number of hyperlinks extracted and processed from a webpage.

Each webpage is processed at most once because the SeenStore prevents duplicate visits. For every processed page, the crawler performs the following operations:

- Remove a URL from the Frontier.
- Check whether it has already been visited.
- Download the webpage.
- Store the webpage.
- Extract hyperlinks.
- Insert newly discovered URLs into the Frontier.

Since network communication dominates the execution time, the overall running time primarily depends on the number of pages crawled and the amount of processing required for each page.

# Section 6 — Future Compatibility

The Crawler has been designed with a modular architecture, allowing future components to be integrated without significant modifications to its core logic.

The current design supports future development in the following ways:

- The crawler stores downloaded webpages using the **PageStorage** component, enabling the Project 03 **Indexer** to access and process the stored pages directly without requiring changes to the crawling process.

- The crawler interacts with other components such as **Frontier**, **SeenStore**, and **PageStorage** through their public interfaces, allowing these components to be replaced or improved independently while preserving the crawler's functionality.

- The crawling logic can be extended to support additional features such as URL filtering, crawl scheduling, or different traversal strategies without affecting the existing architecture.

- The design can be enhanced to support parallel or multi-threaded crawling by modifying the internal execution strategy while retaining the same public API.

