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
    // Builds the inverted index from all stored pages.
    void buildIndex();

private:
    // Components used during indexing.
    PageStorage pageStorage;
    HTMLParser htmlParser;
    Tokenizer tokenizer;
    WordNormalizer wordNormalizer;
    IndexStorage indexStorage;
};

#endif