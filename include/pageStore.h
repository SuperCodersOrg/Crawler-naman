#ifndef PAGE_STORAGE_H
#define PAGE_STORAGE_H

#include <string>
#include <ios>

#include "../../CodeQuotient/include/hashmap.h"
#include "../../CodeQuotient/include/dynamicArray.h"

class PageStorage
{
private:
    std::string filePath;

    // URL -> file offset
    HashMap<std::string, std::streampos> pageIndex;

    // ID -> URL (index = ID - 1)
    DynamicArray<std::string> pageURLs;

    int cachedCount;
    bool initialized;

    void buildIndex();

public:
    PageStorage(const std::string& path = "storage/pages.txt");

    void storePage(const std::string& url,
                   const std::string& html,
                   int depth);

    std::string getPage(const std::string& url);

    std::string getURLByID(int id);

    bool hasPage(const std::string& url);

    int pageCount();
};

#endif