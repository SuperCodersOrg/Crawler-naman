#include <iostream>
#include <string>

#include "indexer.h"
#include "indexStorage.h"
#include "pageStore.h"
#include "../../CodeQuotient/include/dynamicArray.h"

int main()
{
    PageStorage pageStorage;
    IndexStorage indexStorage;

    Indexer indexer(pageStorage, indexStorage);

    std::cout << "=========================================\n";
    std::cout << "Building Inverted Index...\n";
    std::cout << "=========================================\n\n";

    // Build index from stored pages
    indexer.buildIndex();

    // Save the index
    indexStorage.saveToFile("../storage/index.txt");

    std::cout << "Index saved successfully.\n";

    // Clear RAM to test persistence
    indexStorage.clear();

    // Load index back from file
    indexStorage.loadFromFile("../storage/index.txt");

    std::cout << "Index loaded successfully.\n";
    std::cout << "Total Pages Indexed: "
              << pageStorage.pageCount()
              << "\n\n";

    std::string word;

    while (true)
    {
        std::cout << "Enter word to search (type 'exit' to quit): ";
        std::cin >> word;

        if (word == "exit")
        {
            break;
        }

        if (!indexStorage.contains(word))
        {
            std::cout << "Word not found.\n\n";
            continue;
        }

        DynamicArray<int> pages = indexStorage.getPages(word);

        std::cout << "\nFound in:\n";

        for (int i = 0; i < pages.getSize(); i++)
        {
            int pageID = pages[i];

            std::cout << "Page ID: " << pageID
                      << " | URL: "
                      << pageStorage.getURLByID(pageID)
                      << "\n";
        }

        std::cout << "\n";
    }

    return 0;
}