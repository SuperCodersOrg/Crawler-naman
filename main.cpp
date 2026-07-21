#include <iostream>
#include "pageStore.h"

int main()
{
    // Make sure ../storage/pages.txt exists
    PageStorage store("../storage/pages.txt");

    std::cout << "========== PageStorage Tests ==========\n\n";

    // Initially
    std::cout << "Initial Page Count : "
              << store.pageCount()
              << "\n\n";

    // Store first page
    store.storePage(
        "https://example.com",
        "<html><body>Example Page</body></html>",
        0
    );

    // Store second page
    store.storePage(
        "https://google.com",
        "<html><body>Google Page</body></html>",
        1
    );

    std::cout << "After Storing 2 Pages\n";
    std::cout << "Page Count : "
              << store.pageCount()
              << "\n\n";

    // hasPage()
    std::cout << "Contains example.com : "
              << (store.hasPage("https://example.com") ? "Yes" : "No")
              << '\n';

    std::cout << "Contains github.com : "
              << (store.hasPage("https://github.com") ? "Yes" : "No")
              << "\n\n";

    // getPage()
    std::cout << "Retrieved HTML (example.com)\n";
    std::cout << "---------------------------------\n";
    std::cout << store.getPage("https://example.com");
    std::cout << "---------------------------------\n\n";

    // Update existing page
    store.storePage(
        "https://example.com",
        "<html><body>Updated Example Page</body></html>",
        5
    );

    std::cout << "After Updating example.com\n";
    std::cout << "Page Count : "
              << store.pageCount()
              << '\n';

    std::cout << "Updated HTML\n";
    std::cout << "---------------------------------\n";
    std::cout << store.getPage("https://example.com");
    std::cout << "---------------------------------\n\n";

    // Empty URL
    store.storePage("", "<html></html>", 0);

    std::cout << "After Empty URL Insert\n";
    std::cout << "Page Count : "
              << store.pageCount()
              << "\n\n";

    // Non-existing page
    std::cout << "Retrieving Non-existing Page\n";
    std::string html = store.getPage("https://abc.com");

    if (html.empty())
        std::cout << "Page Not Found\n";

    return 0;
}