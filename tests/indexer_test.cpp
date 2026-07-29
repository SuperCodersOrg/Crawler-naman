#include <gtest/gtest.h>

#include "indexer.h"
#include "pageStorage.h"
#include "indexStorage.h"

class IndexerTest : public ::testing::Test
{
protected:
    PageStorage pageStorage{"../storage/test_pages.txt"};
    IndexStorage indexStorage;
    Indexer indexer{pageStorage, indexStorage};

    void SetUp() override
    {
        pageStorage.clear();
        indexStorage.clear();
    }

    void TearDown() override
    {
        pageStorage.clear();
        indexStorage.clear();
    }
};

TEST_F(IndexerTest, EmptyPageStorage)
{
    indexer.buildIndex();

    EXPECT_EQ(indexStorage.wordCount(), 0);
}

TEST_F(IndexerTest, SinglePage)
{
    pageStorage.storePage(
        "https://example.com",
        "<html><body>Hello World</body></html>",
        0);

    indexer.buildIndex();

    EXPECT_TRUE(indexStorage.contains("hello"));
    EXPECT_TRUE(indexStorage.contains("world"));

    DynamicArray<int> pages =
        indexStorage.getPages("hello");

    ASSERT_EQ(pages.getSize(), 1);
    EXPECT_EQ(pages[0], 1);
}

TEST_F(IndexerTest, MultiplePages)
{
    pageStorage.storePage(
        "https://a.com",
        "<body>Hello Apple</body>",
        0);

    pageStorage.storePage(
        "https://b.com",
        "<body>Hello Banana</body>",
        0);

    indexer.buildIndex();

    EXPECT_TRUE(indexStorage.contains("hello"));
    EXPECT_TRUE(indexStorage.contains("apple"));
    EXPECT_TRUE(indexStorage.contains("banana"));

    DynamicArray<int> hello =
        indexStorage.getPages("hello");

    ASSERT_EQ(hello.getSize(), 2);
    EXPECT_EQ(hello[0], 1);
    EXPECT_EQ(hello[1], 2);
}

TEST_F(IndexerTest, DuplicateWordsInSamePage)
{
    pageStorage.storePage(
        "https://example.com",
        "<body>apple apple apple apple</body>",
        0);

    indexer.buildIndex();

    DynamicArray<int> pages =
        indexStorage.getPages("apple");

    ASSERT_EQ(pages.getSize(), 1);
    EXPECT_EQ(pages[0], 1);
}

TEST_F(IndexerTest, IgnoreNumbers)
{
    pageStorage.storePage(
        "https://example.com",
        "<body>123 456 hello 789</body>",
        0);

    indexer.buildIndex();

    EXPECT_FALSE(indexStorage.contains("123"));
    EXPECT_FALSE(indexStorage.contains("456"));
    EXPECT_FALSE(indexStorage.contains("789"));

    EXPECT_TRUE(indexStorage.contains("hello"));
}

TEST_F(IndexerTest, IgnoreEmptyHTML)
{
    pageStorage.storePage(
        "https://example.com",
        "",
        0);

    indexer.buildIndex();

    EXPECT_EQ(indexStorage.wordCount(), 0);
}

TEST_F(IndexerTest, IgnoreScriptContent)
{
    pageStorage.storePage(
        "https://example.com",
        "<body>Hello<script>secret</script>World</body>",
        0);

    indexer.buildIndex();

    EXPECT_TRUE(indexStorage.contains("hello"));
    EXPECT_TRUE(indexStorage.contains("world"));
    EXPECT_FALSE(indexStorage.contains("secret"));
}

TEST_F(IndexerTest, IgnoreStyleContent)
{
    pageStorage.storePage(
        "https://example.com",
        "<body>Hello<style>.x{}</style>World</body>",
        0);

    indexer.buildIndex();

    EXPECT_TRUE(indexStorage.contains("hello"));
    EXPECT_TRUE(indexStorage.contains("world"));
}

TEST_F(IndexerTest, IgnoreComments)
{
    pageStorage.storePage(
        "https://example.com",
        "Hello<!--hidden-->World",
        0);

    indexer.buildIndex();

    EXPECT_TRUE(indexStorage.contains("hello"));
    EXPECT_TRUE(indexStorage.contains("world"));
    EXPECT_FALSE(indexStorage.contains("hidden"));
}

TEST_F(IndexerTest, IndexIsClearedBeforeRebuild)
{
    pageStorage.storePage(
        "https://example.com",
        "<body>apple</body>",
        0);

    indexer.buildIndex();

    EXPECT_TRUE(indexStorage.contains("apple"));

    pageStorage.clear();
    indexStorage.clear();

    pageStorage.storePage(
        "https://example.com",
        "<body>banana</body>",
        0);

    indexer.buildIndex();

    EXPECT_FALSE(indexStorage.contains("apple"));
    EXPECT_TRUE(indexStorage.contains("banana"));
}

TEST_F(IndexerTest, SavesIndexToDisk)
{
    pageStorage.storePage(
        "https://example.com",
        "<body>apple banana</body>",
        0);

    indexer.buildIndex();

    IndexStorage loaded;

    loaded.loadFromFile("../storage/index.txt");

    EXPECT_TRUE(loaded.contains("apple"));
    EXPECT_TRUE(loaded.contains("banana"));
}