#ifndef PAGE_STORAGE_H
#define PAGE_STORAGE_H

#include <string>

class PageStorage {
private:
    std::string filePath;
    int cachedCount;
    bool initialized;

    void initializeCount();

public:
    PageStorage(const std::string& path = "storage/pages.txt");

    void storePage(const std::string& url,
                   const std::string& html,
                   int depth);

    std::string getPage(const std::string& url);

    bool hasPage(const std::string& url);

    int pageCount();
};

#endif