#include "indexer.h"

//---------------------------------------------------------
// Constructor
//---------------------------------------------------------

Indexer::Indexer(PageStorage& pageStorage,
                 IndexStorage& indexStorage)
    : pageStorage(pageStorage),
      indexStorage(indexStorage)
{
}

//---------------------------------------------------------
// Public Method
//---------------------------------------------------------

void Indexer::buildIndex()
{
    // Remove any previously built index.
    indexStorage.clear();

    // Total number of stored pages.
    int totalPages = pageStorage.pageCount();

    // Process every stored page.
    for (int pageID = 1; pageID <= totalPages; pageID++)
    {
        // Retrieve the URL corresponding to this page ID.
        std::string url = pageStorage.getURLByID(pageID);

        // Skip invalid entries.
        if (url.empty())
        {
            continue;
        }

        // Retrieve the HTML of the page.
        std::string html = pageStorage.getPage(url);

        // Skip pages that could not be loaded.
        if (html.empty())
        {
            continue;
        }

        // Extract plain text from the HTML.
        std::string text = htmlParser.extractText(html);

        // Split the text into tokens.
        DynamicArray<std::string> tokens = tokenizer.tokenize(text);

        // Normalize every token and insert it into the index.
        for (int i = 0; i < tokens.getSize(); i++)
        {
            std::string word = wordNormalizer.normalize(tokens[i]);

            // Ignore empty words (stop words, punctuation, etc.).
            if (word.empty())
            {
                continue;
            }
            if (isNumber(word))
            {
                continue;
            }

            indexStorage.insert(word, pageID);
        }
        
    }
    indexStorage.saveToFile("../storage/index.txt");
}

//---------------------------------------------------------
// Getter
//---------------------------------------------------------

IndexStorage& Indexer::getIndexStorage()
{
    return indexStorage;
}

bool Indexer::isNumber(const std::string& word)
{
    if (word.empty())
        return false;

    for (char ch : word)
    {
        if (!std::isdigit(static_cast<unsigned char>(ch)))
        {
            return false;
        }
    }

    return true;
}