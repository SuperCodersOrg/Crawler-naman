#include <iostream>
#include "crawler.h"

int main()
{
    Crawler crawler;

    std::string seedURL = "https://quotes.toscrape.com/";
    int maxDepth = 2;
    int maxPages = 10;

    std::cout << "Starting crawler...\n";
    std::cout << "Seed URL : " << seedURL << '\n';
    std::cout << "Max Depth: " << maxDepth << '\n';
    std::cout << "Max Pages: " << maxPages << "\n\n";

    crawler.crawl(seedURL, maxDepth, maxPages);

    std::cout << "\nCrawler finished.\n";

    return 0;
}