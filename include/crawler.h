#ifndef CRAWLER_H
#define CRAWLER_H

#include <string>
#include <vector>

#include "frontier.h"
#include "seenStore.h"
#include "pageStore.h"
#include "fetcher.h"
#include "urlNormalizer.h"

class Crawler
{
public:
    Crawler();

    void crawl(const std::string& seedURL,
               int maxDepth,
               int maxPages);

private:
    // Core crawler components
    Frontier frontier;
    SeenStore seenStore;
    PageStorage pageStorage;
    Fetcher fetcher;
    URLNormalizer normalizer;

    // Tracks number of pages crawled
    int pageCount;

    // Extract all hyperlinks from downloaded HTML
    void extractLinks(const std::string& html,const std::string& baseURL,int currentDepth,int maxDepth);

    // Determines whether a URL should be visited
    bool shouldVisit(
        const std::string& url,
        int depth,
        int maxDepth
    ) ;
};

#endif