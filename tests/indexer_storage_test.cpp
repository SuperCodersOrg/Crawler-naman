#include <gtest/gtest.h>

#include <fstream>

#include "indexStorage.h"

class IndexStorageTest : public ::testing::Test
{
protected:
    IndexStorage storage;
    const std::string testFile = "../storage/test_index.txt";

    void TearDown() override
    {
        std::remove(testFile.c_str());
    }
};

TEST_F(IndexStorageTest, InitiallyEmpty)
{
    EXPECT_EQ(storage.wordCount(), 0);
}

TEST_F(IndexStorageTest, InsertSingleWord)
{
    storage.insert("apple", 1);

    EXPECT_TRUE(storage.contains("apple"));

    DynamicArray<int> pages = storage.getPages("apple");

    ASSERT_EQ(pages.getSize(), 1);
    EXPECT_EQ(pages[0], 1);
}

TEST_F(IndexStorageTest, InsertMultiplePages)
{
    storage.insert("apple", 1);
    storage.insert("apple", 2);

    DynamicArray<int> pages = storage.getPages("apple");

    ASSERT_EQ(pages.getSize(), 2);

    EXPECT_EQ(pages[0], 1);
    EXPECT_EQ(pages[1], 2);
}

TEST_F(IndexStorageTest, PreventDuplicatePageIDs)
{
    storage.insert("apple", 1);
    storage.insert("apple", 1);

    DynamicArray<int> pages = storage.getPages("apple");

    ASSERT_EQ(pages.getSize(), 1);
    EXPECT_EQ(pages[0], 1);
}

TEST_F(IndexStorageTest, MultipleWords)
{
    storage.insert("apple", 1);
    storage.insert("banana", 2);

    EXPECT_TRUE(storage.contains("apple"));
    EXPECT_TRUE(storage.contains("banana"));

    EXPECT_EQ(storage.wordCount(), 2);
}

TEST_F(IndexStorageTest, EmptyWordIgnored)
{
    storage.insert("", 1);

    EXPECT_EQ(storage.wordCount(), 0);
}

TEST_F(IndexStorageTest, GetPagesUnknownWord)
{
    DynamicArray<int> pages = storage.getPages("orange");

    EXPECT_EQ(pages.getSize(), 0);
}

TEST_F(IndexStorageTest, ClearIndex)
{
    storage.insert("apple", 1);
    storage.insert("banana", 2);

    storage.clear();

    EXPECT_EQ(storage.wordCount(), 0);
    EXPECT_FALSE(storage.contains("apple"));
    EXPECT_FALSE(storage.contains("banana"));
}

TEST_F(IndexStorageTest, SaveEmptyIndex)
{
    storage.saveToFile(testFile);

    std::ifstream in(testFile);

    EXPECT_TRUE(in.is_open());

    std::string line;

    EXPECT_FALSE(std::getline(in, line));
}

TEST_F(IndexStorageTest, SaveAndLoadSingleWord)
{
    storage.insert("apple", 1);

    storage.saveToFile(testFile);

    IndexStorage loaded;

    loaded.loadFromFile(testFile);

    EXPECT_TRUE(loaded.contains("apple"));

    DynamicArray<int> pages = loaded.getPages("apple");

    ASSERT_EQ(pages.getSize(), 1);
    EXPECT_EQ(pages[0], 1);
}

TEST_F(IndexStorageTest, SaveAndLoadMultipleWords)
{
    storage.insert("apple", 1);
    storage.insert("apple", 3);
    storage.insert("banana", 2);

    storage.saveToFile(testFile);

    IndexStorage loaded;

    loaded.loadFromFile(testFile);

    EXPECT_TRUE(loaded.contains("apple"));
    EXPECT_TRUE(loaded.contains("banana"));

    DynamicArray<int> apple = loaded.getPages("apple");

    ASSERT_EQ(apple.getSize(), 2);
    EXPECT_EQ(apple[0], 1);
    EXPECT_EQ(apple[1], 3);

    DynamicArray<int> banana = loaded.getPages("banana");

    ASSERT_EQ(banana.getSize(), 1);
    EXPECT_EQ(banana[0], 2);
}

TEST_F(IndexStorageTest, LoadMissingFile)
{
    IndexStorage loaded;

    loaded.loadFromFile("../storage/does_not_exist.txt");

    EXPECT_EQ(loaded.wordCount(), 0);
}