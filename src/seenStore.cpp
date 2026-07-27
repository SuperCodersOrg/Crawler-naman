#include "seenStore.h"

#include <fstream>
#include <cstdio>

SeenStore::SeenStore()
    : storageFile("../storage/seenStore.txt"),
      dirtyChanges(0)
{
    loadFromDisk();
}

bool SeenStore::contains(const std::string& url)
{
    if (url.empty())
    {
        return false;
    }

    return seenURLs.exists(url);
}

void SeenStore::insert(const std::string& url)
{
    if (url.empty())
    {
        return;
    }

    if (!seenURLs.exists(url))
    {
        seenURLs.set(url, true);
        urlList.append(url);

        dirtyChanges++;

        if (dirtyChanges >= FLUSH_LIMIT)
        {
            flushToDisk();
        }
    }
}

int SeenStore::count()
{
    return seenURLs.getSize();
}

void SeenStore::loadFromDisk()
{
    std::ifstream input(storageFile);

    if (!input.is_open())
    {
        return;
    }

    std::string url;

    while (std::getline(input, url))
    {
        if (url.empty())
        {
            continue;
        }

        seenURLs.set(url, true);
        urlList.append(url);
    }

    input.close();
}

void SeenStore::flushToDisk()
{
    std::ofstream output(storageFile, std::ios::trunc);

    if (!output.is_open())
    {
        return;
    }

    for (int i = 0; i < urlList.getSize(); i++)
    {
        output << urlList[i] << '\n';
    }

    output.close();

    dirtyChanges = 0;
}

void SeenStore::checkpoint()
{
    flushToDisk();
}

void SeenStore::clearDisk()
{
    std::remove(storageFile.c_str());
}