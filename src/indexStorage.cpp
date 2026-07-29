#include "indexStorage.h"

#include <fstream>
#include <sstream>
//---------------------------------------------------------
// Public Methods
//---------------------------------------------------------

void IndexStorage::insert(
    const std::string& word,
    int pageID)
{
    // Ignore empty words.
    if (word.empty())
    {
        return;
    }

    // Word already exists in the index.
    if (invertedIndex.exists(word))
    {
        DynamicArray<int> pages = invertedIndex.get(word);

        // Prevent duplicate page IDs.
        for (int i = 0; i < pages.getSize(); i++)
        {
            if (pages[i] == pageID)
            {
                return;
            }
        }

        pages.append(pageID);
        invertedIndex.set(word, pages);
    }
    else
    {
        DynamicArray<int> pages;
        pages.append(pageID);

        invertedIndex.set(word, pages);
    }
}

DynamicArray<int> IndexStorage::getPages(
    const std::string& word)
{
    if (invertedIndex.exists(word))
    {
        return invertedIndex.get(word);
    }

    return DynamicArray<int>();
}

bool IndexStorage::contains(
    const std::string& word)
{
    return invertedIndex.exists(word);
}

void IndexStorage::clear()
{
    invertedIndex.clear();
}

int IndexStorage::wordCount()
{
    return invertedIndex.getSize();
}

//---------------------------------------------------------
// Save Index to File
//---------------------------------------------------------

void IndexStorage::saveToFile(const std::string& filePath)
{
    std::ofstream out(filePath);

    if (!out.is_open())
    {
        return;
    }

    DynamicArray<std::string> words = invertedIndex.keys();

    for (int i = 0; i < words.getSize(); i++)
    {
        std::string word = words[i];

        out << word << "|";

        DynamicArray<int> pages = invertedIndex.get(word);

        for (int j = 0; j < pages.getSize(); j++)
        {
            out << pages[j];

            if (j != pages.getSize() - 1)
            {
                out << ",";
            }
        }

        out << "\n";
    }

    out.close();
}

void IndexStorage::loadFromFile(const std::string& filePath)
{
    clear();

    std::ifstream in(filePath);

    if (!in.is_open())
    {
        return;
    }

    std::string line;

    while (std::getline(in, line))
    {
        size_t pos = line.find('|');

        if (pos == std::string::npos)
        {
            continue;
        }

        std::string word = line.substr(0, pos);
        std::string pageList = line.substr(pos + 1);

        std::stringstream ss(pageList);
        std::string token;

        while (std::getline(ss, token, ','))
        {
            if (!token.empty())
            {
                insert(word, std::stoi(token));
            }
        }
    }

    in.close();
}