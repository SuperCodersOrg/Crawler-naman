#ifndef INDEXER_H
#define INDEXER_H

#include "pageStore.h"
#include "htmlParser.h"
#include "tokenizer.h"
#include "wordNormalizer.h"
#include "indexStorage.h"

class Indexer
{
public:
    Indexer(PageStorage& pageStorage,
            IndexStorage& indexStorage);
    bool isNumber(const std::string& word);

    void buildIndex();

    IndexStorage& getIndexStorage();

private:
    PageStorage& pageStorage;
    IndexStorage& indexStorage;

    HTMLParser htmlParser;
    Tokenizer tokenizer;
    WordNormalizer wordNormalizer;
};
#endif