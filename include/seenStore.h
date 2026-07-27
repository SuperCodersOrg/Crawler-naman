#ifndef SEENSTORE_H
#define SEENSTORE_H

#include <string>

#include "../../CodeQuotient/include/hashmap.h"
#include "../../CodeQuotient/include/dynamicArray.h"

class SeenStore
{
private:
    HashMap<std::string, bool> seenURLs;
    DynamicArray<std::string> urlList;
    int uniqueCount, duplicateCount;

    // Persistence
    std::string storageFile;
    int dirtyChanges;

    static const int FLUSH_LIMIT = 100;

    void loadFromDisk();
    void flushToDisk();

public:
    SeenStore();

    bool contains(const std::string& url);

    void insert(const std::string& url);

    int count();
    void statsCheck();

    // Force writing the current SeenStore to disk.
    void checkpoint();

    // Delete the persistence file after a successful crawl.
    void clearDisk();
};

#endif