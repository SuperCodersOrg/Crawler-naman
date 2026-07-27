#include <gtest/gtest.h>
#include <cstdio>
#include "seenStore.h"

class SeenStoreTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        std::remove("../storage/seenStore.txt");
    }

    void TearDown() override
    {
        std::remove("../storage/seenStore.txt");
    }
};

// --------------------------------------
// Empty store
// --------------------------------------

TEST_F(SeenStoreTest, InitiallyEmpty)
{
    SeenStore store;

    EXPECT_EQ(store.count(), 0);
    EXPECT_FALSE(store.contains("https://example.com"));
}

// --------------------------------------
// Single insertion
// --------------------------------------

TEST_F(SeenStoreTest, InsertSingleURL)
{
    SeenStore store;

    store.insert("https://example.com");

    EXPECT_TRUE(store.contains("https://example.com"));
    EXPECT_EQ(store.count(), 1);
}

// --------------------------------------
// Duplicate insertion
// --------------------------------------

TEST_F(SeenStoreTest, DuplicateInsertion)
{
    SeenStore store;

    store.insert("https://example.com");
    store.insert("https://example.com");

    EXPECT_EQ(store.count(), 1);
}

// --------------------------------------
// Multiple URLs
// --------------------------------------

TEST_F(SeenStoreTest, MultipleInsertions)
{
    SeenStore store;

    store.insert("https://google.com");
    store.insert("https://github.com");
    store.insert("https://example.com");

    EXPECT_EQ(store.count(), 3);

    EXPECT_TRUE(store.contains("https://google.com"));
    EXPECT_TRUE(store.contains("https://github.com"));
    EXPECT_TRUE(store.contains("https://example.com"));
}

// --------------------------------------
// Empty URL
// --------------------------------------

TEST_F(SeenStoreTest, IgnoreEmptyURL)
{
    SeenStore store;

    store.insert("");

    EXPECT_EQ(store.count(), 0);
    EXPECT_FALSE(store.contains(""));
}

// --------------------------------------
// Unknown URL
// --------------------------------------

TEST_F(SeenStoreTest, URLNotPresent)
{
    SeenStore store;

    store.insert("https://google.com");

    EXPECT_FALSE(store.contains("https://github.com"));
}

// --------------------------------------
// Persistence
// --------------------------------------

TEST_F(SeenStoreTest, CheckpointPersistence)
{
    {
        SeenStore store;

        store.insert("https://google.com");
        store.insert("https://github.com");

        store.checkpoint();
    }

    SeenStore recovered;

    EXPECT_EQ(recovered.count(), 2);

    EXPECT_TRUE(recovered.contains("https://google.com"));
    EXPECT_TRUE(recovered.contains("https://github.com"));
}

// --------------------------------------
// Clear persistence
// --------------------------------------

TEST_F(SeenStoreTest, ClearDisk)
{
    {
        SeenStore store;

        store.insert("https://google.com");
        store.insert("https://github.com");

        store.checkpoint();
        store.clearDisk();
    }

    SeenStore recovered;

    EXPECT_EQ(recovered.count(), 0);
}

// --------------------------------------
// Many URLs
// --------------------------------------

TEST_F(SeenStoreTest, ManyInsertions)
{
    SeenStore store;

    for (int i = 0; i < 100; i++)
    {
        store.insert("https://example.com/" + std::to_string(i));
    }

    EXPECT_EQ(store.count(), 100);

    EXPECT_TRUE(store.contains("https://example.com/0"));
    EXPECT_TRUE(store.contains("https://example.com/50"));
    EXPECT_TRUE(store.contains("https://example.com/99"));
}

// --------------------------------------
// Duplicate after reload
// --------------------------------------

TEST_F(SeenStoreTest, DuplicateAfterReload)
{
    {
        SeenStore store;

        store.insert("https://example.com");
        store.checkpoint();
    }

    SeenStore recovered;

    recovered.insert("https://example.com");

    EXPECT_EQ(recovered.count(), 1);
}

// --------------------------------------
// Multiple checkpoints
// --------------------------------------

TEST_F(SeenStoreTest, MultipleCheckpoints)
{
    SeenStore store;

    store.insert("https://google.com");
    store.checkpoint();

    store.insert("https://github.com");
    store.checkpoint();

    SeenStore recovered;

    EXPECT_EQ(recovered.count(), 2);

    EXPECT_TRUE(recovered.contains("https://google.com"));
    EXPECT_TRUE(recovered.contains("https://github.com"));
}