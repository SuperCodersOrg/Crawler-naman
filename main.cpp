#include <iostream>

#include "crawler.h"
#include "pageStore.h"

int main()
{
    std::cout << "===== Starting Crawler =====\n\n";

    Crawler crawler;

    crawler.crawl(
        "https://quotes.toscrape.com/",
        2,      // Maximum depth
        10      // Maximum pages
    );

    std::cout << "\n===== Crawl Finished =====\n\n";

    PageStorage storage("../storage/pages.txt");

    std::cout << "Total Pages Stored : "
              << storage.pageCount()
              << "\n\n";

    std::string url =
        "https://quotes.toscrape.com/";

    if (storage.hasPage(url))
    {
        std::cout << "Seed page found.\n\n";

        std::string html = storage.getPage(url);

        std::cout << "HTML Size : "
                  << html.size()
                  << "\n\n";

        std::cout << "First 500 characters:\n\n";

        if (html.size() > 500)
        {
            std::cout << html.substr(0, 500);
        }
        else
        {
            std::cout << html;
        }

        std::cout << "\n";
    }
    else
    {
        std::cout << "Seed page not found!\n";
    }

    return 0;
}