#include <gtest/gtest.h>

#include <cstdio>

#include "indexer.h"
#include "indexStorage.h"
#include "pageStore.h"

class IndexerTest : public ::testing::Test
{
protected:
    const std::string pageFile = "../storage/test_pages.txt";
    const std::string indexFile = "../storage/index.txt";

    void SetUp() override
    {
        std::remove(pageFile.c_str());
        std::remove(indexFile.c_str());
    }

    void TearDown() override
    {
        std::remove(pageFile.c_str());
        std::remove(indexFile.c_str());
    }
};

TEST_F(IndexerTest, EmptyStorage)
{
    PageStorage pageStorage(pageFile);
    IndexStorage indexStorage;

    Indexer indexer(pageStorage, indexStorage);

    indexer.buildIndex();

    EXPECT_EQ(indexStorage.wordCount(), 0);
}

TEST_F(IndexerTest, SinglePage)
{
    PageStorage pageStorage(pageFile);
    IndexStorage indexStorage;

    pageStorage.storePage(
        "https://example.com",
        "<html><body>Hello World</body></html>",
        0);

    Indexer indexer(pageStorage, indexStorage);

    indexer.buildIndex();

    EXPECT_TRUE(indexStorage.contains("hello"));
    EXPECT_TRUE(indexStorage.contains("world"));

    DynamicArray<int> pages = indexStorage.getPages("hello");

    EXPECT_EQ(pages.getSize(), 1);
}

TEST_F(IndexerTest, MultiplePages)
{
    PageStorage pageStorage(pageFile);
    IndexStorage indexStorage;

    pageStorage.storePage(
        "https://a.com",
        "<body>Hello Apple</body>",
        0);

    pageStorage.storePage(
        "https://b.com",
        "<body>Hello Banana</body>",
        0);

    Indexer indexer(pageStorage, indexStorage);

    indexer.buildIndex();

    EXPECT_TRUE(indexStorage.contains("hello"));
    EXPECT_TRUE(indexStorage.contains("apple"));
    EXPECT_TRUE(indexStorage.contains("banana"));

    DynamicArray<int> hello =
        indexStorage.getPages("hello");

    EXPECT_EQ(hello.getSize(), 2);
}

TEST_F(IndexerTest, DuplicateWordsStoredOncePerPage)
{
    PageStorage pageStorage(pageFile);
    IndexStorage indexStorage;

    pageStorage.storePage(
        "https://example.com",
        "<body>apple apple apple apple</body>",
        0);

    Indexer indexer(pageStorage, indexStorage);

    indexer.buildIndex();

    DynamicArray<int> pages =
        indexStorage.getPages("apple");

    EXPECT_EQ(pages.getSize(), 1);
}

TEST_F(IndexerTest, IgnoreNumbers)
{
    PageStorage pageStorage(pageFile);
    IndexStorage indexStorage;

    pageStorage.storePage(
        "https://example.com",
        "<body>123 hello 456 world 789</body>",
        0);

    Indexer indexer(pageStorage, indexStorage);

    indexer.buildIndex();

    EXPECT_FALSE(indexStorage.contains("123"));
    EXPECT_FALSE(indexStorage.contains("456"));
    EXPECT_FALSE(indexStorage.contains("789"));

    EXPECT_TRUE(indexStorage.contains("hello"));
    EXPECT_TRUE(indexStorage.contains("world"));
}

TEST_F(IndexerTest, IgnoreScriptContent)
{
    PageStorage pageStorage(pageFile);
    IndexStorage indexStorage;

    pageStorage.storePage(
        "https://example.com",
        "<body>Hello<script>alert(1)</script>World</body>",
        0);

    Indexer indexer(pageStorage, indexStorage);

    indexer.buildIndex();

    EXPECT_TRUE(indexStorage.contains("hello"));
    EXPECT_TRUE(indexStorage.contains("world"));

    EXPECT_FALSE(indexStorage.contains("alert"));
}

TEST_F(IndexerTest, IgnoreStyleContent)
{
    PageStorage pageStorage(pageFile);
    IndexStorage indexStorage;

    pageStorage.storePage(
        "https://example.com",
        "<body>Hello<style>body{color:red;}</style>World</body>",
        0);

    Indexer indexer(pageStorage, indexStorage);

    indexer.buildIndex();

    EXPECT_TRUE(indexStorage.contains("hello"));
    EXPECT_TRUE(indexStorage.contains("world"));

    EXPECT_FALSE(indexStorage.contains("color"));
}

TEST_F(IndexerTest, EmptyHTMLProducesNoIndexEntries)
{
    PageStorage pageStorage(pageFile);
    IndexStorage indexStorage;

    pageStorage.storePage(
        "https://example.com",
        "",
        0);

    Indexer indexer(pageStorage, indexStorage);

    indexer.buildIndex();

    EXPECT_EQ(indexStorage.wordCount(), 0);
}

TEST_F(IndexerTest, SavesIndexToDisk)
{
    PageStorage pageStorage(pageFile);
    IndexStorage indexStorage;

    pageStorage.storePage(
        "https://example.com",
        "<body>Apple Banana</body>",
        0);

    Indexer indexer(pageStorage, indexStorage);

    indexer.buildIndex();

    IndexStorage loaded;

    loaded.loadFromFile(indexFile);

    EXPECT_TRUE(loaded.contains("apple"));
    EXPECT_TRUE(loaded.contains("banana"));
}