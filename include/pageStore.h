#ifndef PAGE_STORAGE_H
#define PAGE_STORAGE_H

#include <string>
#include <cstdint>
#include <ios>

#include "../../CodeQuotient/include/hashmap.h"

class PageStorage
{
private:
    std::string filePath;
    HashMap<std::string, std::streampos> pageIndex;

    int cachedCount;
    bool initialized;

    void buildIndex();

public:
    PageStorage(const std::string& path = "storage/pages.txt");

    void storePage(const std::string& url,const std::string& html,int depth);

    std::string getPage(const std::string& url);

    bool hasPage(const std::string& url);

    int pageCount();
};

#endif