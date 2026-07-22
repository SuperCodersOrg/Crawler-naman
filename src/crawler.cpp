#include "crawler.h"

#include <string>
#include <iostream>

Crawler::Crawler()
    : pageStorage("../storage/pages.txt"),
      pageCount(0)
{
}

bool Crawler::shouldVisit(const std::string& url,int depth,int maxDepth)
{
    if (url.empty())
    {
        return false;
    }

    if (depth > maxDepth)
    {
        return false;
    }

    if (seenStore.contains(url))
    {
        return false;
    }

    return true;
}