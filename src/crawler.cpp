#include "crawler.h"

#include <thread>
#include <chrono>
#include <string>
#include <iostream>
#include <cctype>

Crawler::Crawler()
    : pageStorage("../storage/pages.txt"),
      pageCount(0)
{
}

bool Crawler::shouldVisit(const std::string& url,
                          int depth,
                          int maxDepth)
{
    if (url.empty())
        return false;

    if (depth > maxDepth)
        return false;

    if (seenStore.contains(url))
        return false;

    return true;
}

void Crawler::extractLinks(const std::string& html,
                           const std::string& baseURL,
                           int currentDepth,
                           int maxDepth)
{
    if (currentDepth >= maxDepth)
        return;

    size_t pos = 0;

    while (true)
    {
        pos = html.find("<a", pos);

        if (pos == std::string::npos)
            break;

        size_t hrefPos = html.find("href", pos);

        if (hrefPos == std::string::npos)
        {
            pos += 2;
            continue;
        }

        size_t tagEnd = html.find('>', pos);

        if (tagEnd == std::string::npos || hrefPos > tagEnd)
        {
            pos += 2;
            continue;
        }

        size_t equalPos = html.find('=', hrefPos);

        if (equalPos == std::string::npos)
        {
            pos += 2;
            continue;
        }

        equalPos++;

        while (equalPos < html.length() &&
               std::isspace(static_cast<unsigned char>(html[equalPos])))
        {
            equalPos++;
        }

        if (equalPos >= html.length())
            break;

        char quote = html[equalPos];

        if (quote != '"' && quote != '\'')
        {
            pos = equalPos;
            continue;
        }

        equalPos++;

        size_t endQuote = html.find(quote, equalPos);

        if (endQuote == std::string::npos)
            break;

        std::string link =
            html.substr(equalPos, endQuote - equalPos);

        pos = endQuote + 1;

        if (link.empty())
            continue;

        if (link[0] == '#')
            continue;

        if (link.rfind("javascript:", 0) == 0)
            continue;

        if (link.rfind("mailto:", 0) == 0)
            continue;

        if (link.rfind("tel:", 0) == 0)
            continue;

        std::string normalized =
            normalizer.normalize(link, baseURL);

        if (!shouldVisit(normalized,
                         currentDepth + 1,
                         maxDepth))
        {
            continue;
        }

        frontier.push(
        {
            normalized,
            currentDepth + 1
        });
    }
}

void Crawler::crawl(const std::string& seedURL,
                    int maxDepth,
                    int maxPages)
{
    pageCount = 0;

    std::string normalizedSeed =
        normalizer.normalize(seedURL);

    if (normalizedSeed.empty())
    {
        std::cerr << "Invalid seed URL.\n";
        return;
    }

    frontier.push({normalizedSeed, 0});

    while (!frontier.empty() && pageCount < maxPages)
    {
        URLDepth current = frontier.pop();

        // Check maximum depth
        if (current.depth > maxDepth)
            continue;

        // Already fetched?
        if (seenStore.contains(current.url))
            continue;

        std::string html = fetcher.fetch(current.url);

        if (html.empty())
            continue;

        // Mark as fetched
        seenStore.insert(current.url);

        pageStorage.storePage(current.url,
                            html,
                            current.depth);

        pageCount++;

        extractLinks(html,
                    current.url,
                    current.depth,
                    maxDepth);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Crawling completed.\n";
    std::cout << "Pages Crawled: "
              << pageCount
              << '\n';
}