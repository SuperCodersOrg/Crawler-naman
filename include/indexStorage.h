#ifndef INDEX_STORAGE_H
#define INDEX_STORAGE_H

#include <string>

#include "../../CodeQuotient/include/hashmap.h"
#include "../../CodeQuotient/include/dynamicArray.h"

class IndexStorage
{
public:
    // Inserts a page ID for the given word.
    void insert(const std::string& word,int pageID);
    void saveToFile(const std::string& filePath= "../storage/index.txt");

    void loadFromFile(const std::string& filePath= "../storage/index.txt");

    // Returns all pages containing the word.
    DynamicArray<int> getPages(const std::string& word);

    // Checks whether the word exists in the index.
    bool contains(const std::string& word);

    // Removes all indexed data.
    void clear();

    // Returns the number of indexed words.
    int wordCount();

private:
    // Inverted index:
    // word -> list of page IDs
    HashMap<std::string, DynamicArray<int>> invertedIndex;
    std::string filePath = "../storage/index.txt";
};

#endif